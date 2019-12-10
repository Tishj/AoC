/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 11:44:32 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/11 00:41:23 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

void	del_ast(char **map, t_coord steps, t_coord old, int start, int max_size)
{
	t_coord current;
	t_coord goal;

	current.y = old.y + steps.y;
	current.x = old.x + steps.x;
	if (is_it_safe(map, current, max_size) == 0)
		return ;
	printf("checking %3d, %3d | stepsize: %3d, %3d\n", current.y, current.x, steps.y, steps.x);
	if (map[current.y][current.x] == '#')
	{
		if (start != 1)
		{
			printf("DEL y:%3d, x:%3d | with step size: y:%3d, x:%3d\n", current.y, current.x, steps.y, steps.x);
			map[current.y][current.x] = 'R';
		}
		start = 0;
	}
	return (del_ast(map, steps, current, start, max_size));
}

int		nb_flip(int nb)
{
	if (nb < 0)
		return (-1);
	return (1);
}

t_coord	set_course(t_stepper data)
{
	t_coord course;

	course.x = data.total.x - data.start.x;
	course.y = data.total.y - data.start.y;
	if (course.x != 0 && course.y != 0)
		if (course.x / course.y == 1 && course.y % course.x == 0)
		{
			course.x = 1 * nb_flip(course.x);
			course.y = 1 * nb_flip(course.y);
		}
	if (data.total.x == 0)
	{
		course.x = 0;
		course.y = 1 * nb_flip(course.y);
	}
	if (data.total.y == 0)
	{
		course.x = 1 * nb_flip(course.x);
		course.y = 0;
	}
//	printf("nop\n");
	return (course);
}

void	scout_ast(char **map, t_stepper data, int max_size) //recursively step $steps every time, counting the total, to give to del_ast if a # is encountered
{
	t_coord current;

	current.y = (data.start.y + data.total.y) + data.step.y;
	current.x = (data.start.x + data.total.x) + data.step.x;
	if (is_it_safe(map, current, max_size) == 0)
		return ;
	data.total.x += data.step.x;
	data.total.y += data.step.y;
	printf("%c | currently on: y%3d, x%3d | steps taken: y: %3d | x: %3d |||| step size: y: %3d | x: %3d\n", map[current.y][current.x], current.y, current.x, data.total.y, data.total.x, data.step.y, data.step.x);
	if (map[current.y][current.x] == '#')
	{
		data.total = set_course(data);
		if (data.total.x == 0 && data.total.y == 0)
			return ;
		return (del_ast(map, data.total, current, 0, max_size));
	}
	return (scout_ast(map, data, max_size));
}

void	find_asteroid(char **map, t_coord start, int max_size) //this function will start at an asteroid, and send step_ast in each direction
{
	t_coord step;
	t_stepper data;

	data.start = start;
	data.total.x = 0;
	data.total.y = 0;
	step.y = -max_size;
	while (step.y < max_size)
	{
		step.x = -max_size;
		while (step.x < max_size)
		{
			if (step.x != 0 || step.y != 0)
			{
				data.step.x = step.x;
				data.step.y = step.y;
				scout_ast(map, data, max_size); //a scout is send to every possible spot
			}
			step.x++;
		}
		step.y++;
	}
}

int		check_possibilities(char **map, int max_size)
{
	int		tmp_ast;
	int		max_ast;
	t_coord	coords;
	char	**dup;
	char	**best;
	t_coord b_coords;

	coords.y = 0;
	max_ast = 0;
	while (map[coords.y])
	{
		coords.x = 0;
		while (map[coords.y][coords.x])
		{
			if (map[coords.y][coords.x] == '#')
			{
				dup = dup_array(map);
				find_asteroid(dup, coords, max_size);			//is called when an asteroid is found
				tmp_ast = get_total(dup) - 1;
				if (tmp_ast > max_ast)
				{
					b_coords = coords;
					best = dup_array(dup);
					max_ast = tmp_ast;
				}
				free(dup);
			}
			coords.x++;
		}
		coords.y++;
	}
	printf("Best location: %d,%d\n", b_coords.x, b_coords.y);
	print_array(best, b_coords);
	return (max_ast);
}

int		main(int argc, char **input)
{
	int fd;
	char **map;
	char **dup;
	int max_size;
	t_coord pos;

	if (argc < 2)
		return (0);
	fd = open(input[1], O_RDONLY);
	map = get_array(fd, &max_size);
//	pos.x = 4;
//	pos.y = 4;
//	find_asteroid(map, pos, max_size);
//	print_array(map, pos);
//	printf("max: %d\n", get_total(map));
	printf("Maximum visible asteroids: %d\n", check_possibilities(map, max_size));
//	dup = dup_array(map);
//	print_array(dup);
	return (0);
}
