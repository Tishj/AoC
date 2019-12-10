/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 11:44:32 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/10 19:09:31 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

void	print_array(char **array, t_coord coords)
{
	int x;
	int y;

	y = 0;
	while (array[y])
	{
		x = 0;
		while (array[y][x])
		{
			if (x == coords.x && y == coords.y)
			{
				printf("\033[1;32m");
				printf("X");
				printf("\033[0m");
			}
			else if (array[y][x] == 'R')
			{
				printf("\033[1;31m");
				printf("#");
				printf("\033[0m");
			}
			else
				printf("%c", array[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

char	**dup_array(char **map)
{
	int		y;
	int		x;
	char	**dup;

	y = 0;
	dup = malloc(sizeof(char *) * (39 + 1));
	while (map[y])
	{
		x = 0;
		dup[y] = malloc(sizeof(char) * (39 + 1));
		while (map[y][x])
		{
			dup[y][x] = map[y][x];
			x++;
		}
		dup[y][x] = 0;
		y++;
	}
	dup[y] = 0;
	return (dup);
}

char	**get_array(int fd)
{
	int		red;
	char	c;
	char	**array;
	char	*firstline;
	int		i;

	i = 0;
	get_next_line(fd, &firstline);
	g_size = strlen(firstline);
	array = malloc(sizeof(char *) * (g_size + 1));
	array[i] = firstline;
	i++;
	while (i < g_size)
	{
		get_next_line(fd, &array[i]);
		i++;
	}
	array[i] = 0;
	return (array);
}

int		get_total(char **map)
{
	int ast;
	int x;
	int y;

	y = 0;
	ast = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '#')
				ast++;
			x++;
		}
		y++;
	}
	return (ast);
}

int		is_it_safe(char **map, t_coord start, t_coord goal)
{
//	printf("Checking if there is safe passage between %d,%d to %d,%d...\n", start.y, start.x, goal.y, goal.x);
	if ((goal.x < g_size && goal.x > 0) && (goal.y < g_size && goal.y > 0))
		return (1);
	else
		return (0);
	while (map[start.y] && start.y >= 0)
	{
		while (map[start.y][start.x] && start.x >= 0)
		{
			if (start.x == goal.x && start.y == goal.y)
			{
				printf("The answer is yes\n");
				return (1);
			}
			start.x++;
		}
		start.x = 0;
		start.y++;
	}
	printf("The answer is no\n");
	return (0);
}

void	del_ast(char **map, t_coord steps, t_coord old, int start)
{
	t_coord to;
	t_coord goal;

	to.y = old.y + steps.y;
	to.x = old.x + steps.y;
	if (is_it_safe(map, old, to) == 0)
		return ;
	if (map[to.y][to.x] == '#')
	{
		if (start != 1)
		{
			printf("steps I took: y%d,x%d | I came from y%d,x%d\n", steps.y, steps.x, old.y, old.x);
			map[to.y][to.x] = 'R';
		}
		start = 0;
	}
	return (del_ast(map, steps, to, start));
}

t_coord	set_course(t_stepper data)
{
	t_coord course;

	course = data.total;
	if (data.step.x / data.step.y == 1 && data.step.x % data.step.y == 0)
	{
		course.x = 1;
		course.y = 1;
		if (data.step.x < 0)
			course.x *= -1;
		if (data.step.y < 0)
			course.y *= -1;
	}
	else if (data.step.x == 0)
	{
		course.x = 0;
		course.y = 1;
		if (data.step.x < 0)
			course.x *= -1;
		if (data.step.y < 0)
			course.y *= -1;
	}
	else if (data.step.y == 0)
	{
		course.x = 1;
		course.y = 0;
		if (data.step.x < 0)
			course.x *= -1;
		if (data.step.y < 0)
			course.y *= -1;
	}
	return (course);
}

void	step_ast(char **map, t_stepper data) //recursively step $steps every time, counting the total, to give to del_ast if a # is encountered
{
	t_coord start;
	t_coord goal;

	start.x = (data.start.x + data.total.x);
	start.y = (data.start.y + data.total.y);
	goal.y = (data.start.y + data.total.y) + data.step.y;
	goal.x = (data.start.x + data.total.x) + data.step.x;
	if (is_it_safe(map, start, goal) == 0)
		return ;
//	printf("Segfault?\n");
	if (map[goal.y][goal.x] == '#')
	{
//		printf("No?\n");
		data.total.x += data.step.x;
		data.total.y += data.step.y;
		data.total = set_course(data);
		printf("steps to take: y: %d | x: %d\n", data.total.y, data.total.x);
		del_ast(map, data.total, goal, 1);
//		map[goal.y][goal.x] == '#';
	}
//	return (step_ast(map, data));
}

void	find_asteroid(char **map, t_coord start) //this function will start at an asteroid, and send step_ast in each direction
{
	t_coord step;
	t_stepper data;

	data.start = start;
	data.total.x = 0;
	data.total.y = 0;
	step.y = -g_size;
	while (step.y < g_size)
	{
		step.x = -g_size;
		while (step.x < g_size)
		{
//			printf("step.y: %4d | step.x %4d\n", step.y, step.x);
			if (step.x != 0 && step.y != 0)
			{
				data.step = step;
				step_ast(map, data);
			}
			step.x++;
		}
		step.y++;
	}
}

int		check_possibilities(char **map)
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
				find_asteroid(dup, coords);			//is called when an asteroid is found
				tmp_ast = get_total(dup);
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
	printf("Best location: %d,%d\n", b_coords.y, b_coords.x);
	print_array(best, b_coords);
	return (max_ast);
}

int		main(int argc, char **input)
{
	int fd;
	char **map;
	char **dup;
	t_coord pos;

	if (argc < 2)
		return (0);
	fd = open(input[1], O_RDONLY);
	map = get_array(fd);
	pos.x = 6;
	pos.y = 3;
	find_asteroid(map, pos);
	print_array(map, pos);
	printf("max: %d\n", get_total(map));
//	printf("Maximum visible asteroids: %d\n", check_possibilities(map));
//	dup = dup_array(map);
//	print_array(dup);
	return (0);
}
