/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ray.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 16:49:14 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/29 16:49:14 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

t_ray	ft_ray_init(t_coord pos, t_fcoord step)
{
	t_ray	new;

	new.stp = step;
	new.ttl.x = 0.0;
	new.ttl.y = 0.0;
	new.pos = pos;
	return (new);
}
