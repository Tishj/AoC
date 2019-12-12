/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_moon_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 11:22:01 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/12 16:28:56 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day12.h"

t_moon	*moon_new(t_coord pos, t_coord vel)
{
	t_moon *new;

	new = malloc(sizeof(t_moon));
	new->next = NULL;
	new->pos = pos;
	new->vel = vel;
	return (new);
}

void	moon_addbck(t_moon **start, t_moon *new)
{
	t_moon	*iter;
	t_moon	*last;

	if (start == NULL)
		return ;
	if (*start == NULL)
	{
		*start = new;
		return ;
	}
	iter = *start;
	while (iter)
	{
		last = iter;
		iter = iter->next;
	}
	last->next = new;
}

t_moon	*init_moons(void)
{
	t_moon *moons;
	t_moon *current;
	t_coord pos;
	t_coord vel;

	moons = NULL;
	vel.x = 0;
	vel.y = 0;
	vel.z = 0;
	pos.x = -15;
	pos.y = 1;
	pos.z = 4;
	current = moon_new(pos, vel);
	moon_addbck(&moons, current);
	pos.x = 1;
	pos.y = -10;
	pos.z = -8;
	current = moon_new(pos, vel);
	moon_addbck(&moons, current);
	printf("testerino\n");
	pos.x = -5;
	pos.y = 4;
	pos.z = 9;
	current = moon_new(pos, vel);
	moon_addbck(&moons, current);
	pos.x = 4;
	pos.y = 6;
	pos.z = -2;
	current = moon_new(pos, vel);
	moon_addbck(&moons, current);
	return (moons);
}
