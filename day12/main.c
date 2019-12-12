/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 11:07:48 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/12 16:29:08 by tbruinem      ########   odam.nl         */
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
	if (c2 > c1)
		return (1);
	if (c2 < c1)
		return (-1);
	return (0);
}

int		nb_flip(int orig)
{
	if (orig < 0)
		return (orig * -1);
	return (orig);
}

t_moon	*update_moon(t_moon **start, t_moon *current)
{
	t_moon	*list;
	t_moon	*new;

	list = *start;
	new = moon_new(current->pos, current->vel);
	while (list)
	{
		new->vel.x += get_offset(current->pos.x, list->pos.x);
		new->vel.y += get_offset(current->pos.y, list->pos.y);
		new->vel.z += get_offset(current->pos.z, list->pos.z);
		list = list->next;
	}
	new->pos.x += new->vel.x;
	new->pos.y += new->vel.y;
	new->pos.z += new->vel.z;
	return (new);
}

t_moon	*time_skip(t_moon **moons)
{
	int		step;
	t_moon	*new;
	t_moon	*newlst;
	t_moon	*olditer;

	step = 0;
	newlst = NULL;
	olditer = *moons;
	while (step < 1000)
	{
		printf("step %d\n", step);
		print_moons(*moons);
		while (olditer)
		{
			new = update_moon(moons, olditer);
			moon_addbck(&newlst, new);
			olditer = olditer->next;
		}
		*moons = newlst;
		olditer = *moons;
		newlst = NULL;
		step++;
	}
	return (*moons);
}

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

int		main(void)
{
	int		energy;
	t_moon	*moons;

	moons = init_moons();
//	print_moons(moons);
	energy = get_total_energy(moons);
//	printf("Total energy: %d\n");
	return (0);
}
