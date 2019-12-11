/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_part2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 11:44:32 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/11 21:21:02 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

void	del_ast(char **map, t_coord steps, t_coord old, int max_size)
{
	t_coord current;
	t_coord goal;

	current.y = old.y + steps.y;
	current.x = old.x + steps.x;
	if (is_it_safe(map, current, max_size) == 0)
		return ;
	if (map[current.y][current.x] == '#')
	{
		map[current.y][current.x] = 'R';
		return ;
	}
	return (del_ast(map, steps, current, max_size));
}

int		nb_flip(int nb)
{
	if (nb < 0)
		return (-1);
	return (1);
}

t_coord	set_course(t_stepper data, int max_size)
{
	t_coord course;
	int div;

	course.x = data.total.x;
	course.y = data.total.y;
	if (course.x != 0 && course.y != 0)
	{
		div = get_div(course, max_size);
		if (div != 0)
		{
			course.x = course.x / (div * nb_flip(div));
			course.y = course.y / (div * nb_flip(div));
		}
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
	return (course);
}

void	scout_ast(char **map, t_stepper data, int max_size)
{
	t_coord current;

	current.y = (data.start.y + data.total.y) + data.step.y;
	current.x = (data.start.x + data.total.x) + data.step.x;
	if (is_it_safe(map, current, max_size) == 0)
		return ;
	data.total.x += data.step.x;
	data.total.y += data.step.y;
	if (map[current.y][current.x] == '#')
	{
		data.total = set_course(data, max_size);
		if (data.total.x == 0 && data.total.y == 0)
			return ;
		return (del_ast(map, data.total, current, max_size));
	}
	return (scout_ast(map, data, max_size));
}

void	find_asteroid(char **map, t_coord start, int max_size)
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
				scout_ast(map, data, max_size);
			}
			step.x++;
		}
		step.y++;
	}
}

int		get_cycle(t_coord goal, int max_size, int cycle)
{
	int ret;

	if (goal.y == 0 && goal.x == (max_size - 1) / 2)
		ret = 0;
	else if (goal.y == 0 && goal.x == (max_size - 1))
		ret = 1;
	else if (goal.y == (max_size - 1) && goal.x == (max_size - 1))
		ret = 2;
	else if (goal.y == (max_size - 1) && goal.x == 0)
		ret = 3;
	else if (goal.y == 0 && goal.x == 0)
		ret = 4;
	else
		ret = cycle;
	if (ret != cycle)
		printf("New cycle: %d\n", ret);
	return (ret);
}

t_coord	smallest_step(t_coord orig)
{
	printf("original step: y%d, x%d\n", orig.y, orig.x);
	if (orig.x == 0 && orig.y != 0)
		orig.y /= (orig.y * nb_flip(orig.y));
	else if (orig.y == 0 && orig.x != 0)
		orig.x /= (orig.x * nb_flip(orig.x));
	else if (orig.y != 0 && orig.x != 0)
	{
		if (orig.y % orig.x == 0)
		{
			orig.y /= (orig.x * nb_flip(orig.x));
			orig.x /= (orig.x * nb_flip(orig.x));
		}
		else if (orig.x % orig.y == 0)
		{
			orig.y /= (orig.y * nb_flip(orig.y));
			orig.x /= (orig.y * nb_flip(orig.y));
		}
	}
	printf("new step: y%d, x%d\n", orig.y, orig.x);
	return (orig);
}

void	vaporizer(char **map, int max_size)
{
	t_coord goal;
	t_coord step;
	t_coord start;
	int ast;
	int cyc;

	start.x = max_size / 2;
	start.y = max_size / 2;
	goal.y = 0;
	goal.x = max_size / 2;
	ast = get_total(map);
	cyc = 0;
	while (ast)
	{
		step = goal;
		step.x -= start.x;
		step.y -= start.y;
		step = smallest_step(step);
		printf("ast: %d | goal: y%d, x%d\n", ast, goal.y, goal.x);
		del_ast(map, step, start, max_size);
		cyc = get_cycle(goal, max_size, cyc);
		if (cyc == 0 || cyc == 4)
			goal.x++;
		if (cyc == 1)
			goal.y++;
		if (cyc == 2)
			goal.x--;
		if (cyc == 3)
			goal.y--;
		print_array(map, goal);
		sleep(1);
		ast = get_total(map);
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
				find_asteroid(dup, coords, max_size);
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
	vaporizer(map, max_size);
//	printf("Maximum visible asteroids: %d\n", check_possibilities(map, max_size));
	return (0);
}
