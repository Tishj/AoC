/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 23:19:53 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/10 23:19:53 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

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

int		is_it_safe(char **map, t_coord goal, int max_size)
{
//	printf("Checking if %d,%d falls within the array\n", goal.y, goal.x);
	if ((goal.x < max_size && goal.x >= 0) && (goal.y < max_size && goal.y >= 0))
		return (1);
	else
		return (0);
}
