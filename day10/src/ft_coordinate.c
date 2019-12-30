/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_coordinate.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 12:48:44 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/29 12:48:44 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

t_coord		ft_coord_init(int x, int y)
{
	t_coord start;

	start.x = x;
	start.y = y;
	return (start);
}
