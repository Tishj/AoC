/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_direction.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 12:40:49 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/29 12:40:49 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

/*
Q_TOPRIGHT:
X = 0	-> 1
Y = -1	-> 0

Q_BOTRIGHT:
X = 1	-> 0
Y = 0	-> 1

Q_BOTLEFT;
X = 0	-> -1
Y = 1	-> 0

Q_TOPLEFT:
X = -1	-> 0
Y = 0	-> -1
*/

int		ft_direction_get(t_fcoord step, int cycle)
{
	int ret;

	if (step.y <= -1.0 && step.x >= 0.0 && cycle == Q_TOPLEFT)
		ret = Q_TOPRIGHT;
	else if (step.y >= 0.0 && step.x >= 1.0 && cycle == Q_TOPRIGHT)
		ret = Q_BOTRIGHT;
	else if (step.y >= 1.0 && step.x <= 0.0 && cycle == Q_BOTRIGHT)
		ret = Q_BOTLEFT;
	else if (step.y <= 0.0 && step.x <= -1.0 && cycle == Q_BOTLEFT)
		ret = Q_TOPLEFT;
	else
		ret = cycle;
	return (ret);
}

t_fcoord		ft_direction_translate(int dir, t_fcoord orig)
{
	t_fcoord goal;

	if (dir == Q_TOPRIGHT)
		goal = ft_fcoord_init(orig.x + 0.001, orig.y + 0.001);
	if (dir == Q_BOTRIGHT)
		goal = ft_fcoord_init(orig.x - 0.001, orig.y + 0.001);
	if (dir == Q_BOTLEFT)
		goal = ft_fcoord_init(orig.x - 0.001, orig.y - 0.001);
	if (dir == Q_TOPLEFT)
		goal = ft_fcoord_init(orig.x + 0.001, orig.y - 0.001);
	return (goal);
}
