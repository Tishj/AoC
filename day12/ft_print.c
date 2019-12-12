/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 13:00:57 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/12 13:06:47 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day12.h"

void	print_moons(t_moon *moons)
{
	int i;

	i = 0;
	while (moons)
	{
		printf("moon: %d | pos: x%3d,y%3d,z%3d | vel: x%3d,y%3d,z%3d\n",
		i, moons->pos.x, moons->pos.y, moons->pos.z,
		moons->vel.x, moons->vel.y, moons->vel.z);
		i++;
		moons = moons->next;
	}
}
