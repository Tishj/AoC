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

int		get_div(t_coord course, int max_size)
{
	int div;

	div = max_size;
	while (div >= 2)
	{
		if (course.x % div == 0 && course.y % div == 0)
			return (div);
		div--;
	}
	return (0);
}

int		nb_flip(int nb)
{
	if (nb < 0)
		return (-1);
	return (1);
}

int		is_it_safe(char **map, t_coord goal, int max_size)
{
//	printf("Checking if %d,%d falls within the array\n", goal.y, goal.x);
	if ((goal.x < max_size && goal.x >= 0) && (goal.y < max_size && goal.y >= 0))
		return (1);
	else
		return (0);
}
