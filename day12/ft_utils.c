/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 12:54:07 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/13 12:54:07 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day12.h"

int		get_diff(t_moon *orig, t_moon *current, int diff)
{
/* 	printf("comparing..\n");
	printf("pos\ncurrent x %d | orig x%d\n", current->pos.x, orig->pos.x);
	printf("current y %d | orig y%d\n", current->pos.y, orig->pos.y);
	printf("current z %d | orig z%d\n", current->pos.z, orig->pos.z);
	printf("vel\ncurrent x %d | orig x%d\n", current->vel.x, orig->vel.x);
	printf("current y %d | orig y%d\n", current->vel.y, orig->vel.y);
	printf("current z %d | orig z%d\n", current->vel.z, orig->vel.z); */
	diff += (orig->pos.x - current->pos.x);
	diff += (orig->pos.y - current->pos.y);
	diff += (orig->pos.z - current->pos.z);
//	printf("difference %d\n", diff);
	return (diff);
}

t_coord	reset_coords(void)
{
	t_coord base;

	base.x = 0;
	base.y = 0;
	base.z = 0;
	return (base);
}

int		get_offset(int c1, int c2)
{
	int ret;

	ret = 0;
	if (c2 > c1)
		ret = 1;
	if (c2 < c1)
		ret = -1;
	return (ret);
}

int		nb_flip(int orig)
{
	if (orig < 0)
		return (orig * -1);
	return (orig);
}
