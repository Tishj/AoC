/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_part1.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 12:56:27 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/13 12:56:27 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day12.h"

int		get_sum(t_moon *moons, char c)
{
	int ret;

	ret = 0;
	if (c == 'p')
	{
		while (moons)
		{
			ret += nb_flip(moons->pos.x);
			ret += nb_flip(moons->pos.y);
			ret += nb_flip(moons->pos.z);
			moons = moons->next;
		}
	}
	if (c == 'k')
	{
		while (moons)
		{
			ret += nb_flip(moons->vel.x);
			ret += nb_flip(moons->vel.y);
			ret += nb_flip(moons->vel.z);
			moons = moons->next;
		}
	}
	return (ret);
}

int		get_total_energy(t_moon *moons)
{
	t_moon	*final;
	int		ret;

	ret = 0;
	final = time_skip(&moons);
	while (moons)
	{
		ret += get_planet_energy(moons->pos, moons->vel);
		moons = moons->next;
	}
	printf("Total: %d\n", ret);
	return (ret);
}

int		get_planet_energy(t_coord pos, t_coord vel)
{
	int kin;
	int pot;

	printf("pos\nx %d, y %d, z %d\n", pos.x, pos.y, pos.z);
	printf("vel\nx %d, y %d, z %d\n", vel.x, vel.y, vel.z);
	kin = nb_flip(vel.x) + nb_flip(vel.y) + nb_flip(vel.z);
	pot = nb_flip(pos.x) + nb_flip(pos.y) + nb_flip(pos.z);
	printf("Potential %d | Kinetic %d | Total: %d\n", pot, kin, kin * pot);
	return (kin * pot);
}
