/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 13:37:57 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/04 21:57:05 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day3.h"

t_coords	*lst_new(int x, int y)
{
	t_coords *new;

	new = (t_coords *)malloc(sizeof(t_coords));
	if (!new)
		return (NULL);
	new->x = x;
	new->y = y;
	new->next = NULL;
	return (new);
}

int		get_move(t_move *move, int fd)
{
	int		red;
	char	c[1];
	int		res;

	res = 0;
	red = read(fd, c, 1);
	while (red > 0 && *c != '\n' && *c != ',')
	{
		if (*c == 'D' || *c == 'U' || *c == 'R' || *c == 'L')
			move->direction = *c;
		else if (*c >= '0' && *c <= '9')
			res = res * 10 + (*c - '0');
		red = read(fd, c, 1);
	}
	move->amount = res;
	if (*c == ',')
		return (1);
	return (0);
}

void	lst_addback(t_coords **map, t_coords *new)
{
	t_coords	*unit;
	t_coords	*tmp;

	unit = *map;
	if (unit == NULL)
	{
		unit = new;
		return ;
	}
	while (unit)
	{
		tmp = unit;
		unit = unit->next;
	}
	tmp = new;
}

void	translate_move(t_move move, char c, int *x, int *y)
{
	if (c == 'x')
	{	
		if (move.direction == 'R')
			*x = *x + move.amount;
		if (move.direction == 'L')
			*x = *x - move.amount;
	}
	if (c == 'y')
	{
		if (move.direction == 'U')
			*y = *y + move.amount;
		if (move.direction == 'D')
			*y = *y - move.amount;
	}
}

t_coords	*make_move(t_move move, t_coords *map, int cur_x, int cur_y)
{
	int x = cur_x;
	int y = cur_y;

	translate_move(move, 'x', &x, &y);
	translate_move(move, 'y', &x, &y);
//	printf("OLD\nx:%d | y:%d | cur_x:%d | cur_y:%d\n", x, y, cur_x, cur_y);
	while (cur_x != x || cur_y != y)
	{
		if ((x - cur_x) > 0)
			cur_x++;
		else if ((x - cur_x) < 0)
			cur_x--;
		if ((y - cur_y) > 0)
			cur_y++;
		else if ((y - cur_y) < 0)
			cur_y--;
		map->next = lst_new(cur_x, cur_y);
		map = map->next;
	}
//	printf("NEW\nx:%d | y:%d | cur_x:%d | cur_y:%d\n", x, y, cur_x, cur_y);
	return (map);
}

t_coords	*make_map(int fd)
{
	int			result;
	t_move		move;
	t_coords	*map_start;
	t_coords	*map;
	int			tmp;

	map_start = lst_new(0, 0);
	map = map_start;
	tmp = get_move(&move, fd);
//	printf("Direction: %c%d\n", move.direction, move.amount);
	while (tmp >= 0)
	{
//		printf("Direction: %c%d\n", move.direction, move.amount);
		map = make_move(move, map, map->x, map->y);
		if (tmp == 0)
			break ;
		tmp = get_move(&move, fd);
	}
	return (map_start);
}

int		is_collision(t_coords *wire1, t_coords *wire2)
{
	if (wire1->x == 0 && wire1->y == 0)
		return (0);
	if (wire1->x == wire2->x && wire1->y == wire2->y)
	{
//		printf("x:%d | x:%d\ny:%d | y:%d\n\n", wire1->x, wire2->x, wire1->y, wire2->y);
		return (1);
	}
	return (0);
}

int			get_middle(t_coords *wire1, t_coords *wire2, char c)
{
	int			res;
	t_coords	*tmp;

	res = 0;
	tmp = wire2;
	if (c == 'y')
		while (wire1)
		{
			while(tmp)
			{
				if (wire1->y > res)
					res = wire1->y;
				if (tmp->y > res)
					res = tmp->y;
				tmp = tmp->next;
			}
			tmp = wire2;
			wire1 = wire1->next;
		}
	if (c == 'x')
		while (wire1)
		{
			while(tmp)
			{
				if (wire1->y > res)
					res = wire1->y;
				if (tmp->y > res)
					res = tmp->y;
				tmp = tmp->next;
			}
			tmp = wire2;
			wire1 = wire1->next;
		}
	return (res / 2);
}

int		get_distance(int cur_x, int cur_y)
{
	int res;
	if (cur_x < 0)
		cur_x = cur_x * -1;
	if (cur_y < 0)
		cur_y = cur_y * -1;
	res = cur_x + cur_y;
	return (res);
}

int		find_collisions(t_coords **wire1, t_coords **wire2)
{
	t_coords	*tmp;
	t_coords	*wire;
	int start = 1;
	int			s_dist;
	int			tmp_dist;
	int			middle_x = 0;
	int			middle_y = 0;
	int			collision;
	int			w1_s = 0;
	int			w2_s = 0;
	int			total = 0;

	wire = *wire1;
	tmp = *wire2;
	s_dist = 0;
	collision = 0;
	while (wire)
	{
		w2_s = 0;
		while (tmp)
		{
			collision = is_collision(wire, tmp);
			if (collision == 1)
			{
				tmp_dist = get_distance(tmp->x, tmp->y);
	//			printf("x:%d | y:%d | tmp_dist: %d\n", tmp->x, tmp->y, tmp_dist);
//				printf("dist:%d | wire1: %d, wire2: %d\n", tmp_dist, w1_s, w1_s);
//				if (s_dist > tmp_dist || start == 1)
//				{
//					s_dist = tmp_dist;
//					printf("dist:%d | wire1: %d, wire2: %d\n", s_dist, w1_s, w1_s);
//					start = 0;
//				}
				if (w1_s + w2_s < total || start == 1)
				{
					total = w1_s + w2_s;
					start = 0;
					printf("total: %d\n", total);
				}
			}
			tmp = tmp->next;
			w2_s++;
		}
		tmp = *wire2;
		wire = wire->next;
		w1_s++;
	}
	return (s_dist);
}

void	print_wire(t_coords *wire, int nb)
{
	while (wire)
	{
		printf("wire%d | x%d:y%d\n", nb, wire->x, wire->y);
		wire = wire->next;
	}
}

int		main(int argc, char **input)
{
	t_coords	*wire1;
	t_coords	*wire2;
	t_collision	*list;
	int fd;

	fd = 0;
	if (argc > 1)
		fd = open(input[1], O_RDONLY);
	wire1 = make_map(fd);
	wire2 = make_map(fd);
//	print_wire(wire1, 1);
//	print_wire(wire2, 2);
//	return (0);
	printf("%d\n", find_collisions(&wire1, &wire2));
}
