/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_part2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 11:44:32 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/29 17:23:40 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

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

/* int		check_possibilities(char **map, int max_size)
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
				dup = ft_map_dup(map);
				ft_asteroid_find(dup, coords, max_size);
				tmp_ast = ft_asteroid_count(dup) - 1;
				if (tmp_ast > max_ast)
				{
					b_coords = coords;
					best = ft_map_dup(dup);
					max_ast = tmp_ast;
				}
				free(dup);
			}
			coords.x++;
		}
		coords.y++;
	}
	printf("Best location: %d,%d\n", b_coords.x, b_coords.y);
//	print_array(best, b_coords);
	return (max_ast);
}
 */