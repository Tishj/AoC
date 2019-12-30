/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_fcoord.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 13:38:16 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/29 13:38:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

int			ft_fcoord_isround(t_fcoord coord)
{
	int x;
	int y;

	x = (coord.x == 0) ? 0 : (int)(coord.x * 10);
	y = (coord.y == 0) ? 0 : (int)(coord.y * 10);
	x = (x == 0) ? x : x % 10;
	y = (y == 0) ? y : y % 10;
	if (x == 0 && y == 0)
		return (1);
	return (0);
}

t_fcoord	ft_fcoord_init(float x, float y)
{
	t_fcoord new;

	new.x = x;
	new.y = y;
	return (new);
}
