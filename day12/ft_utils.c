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
