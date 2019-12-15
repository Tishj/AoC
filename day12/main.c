/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 11:07:48 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/14 21:21:09 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day12.h"

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

int		moon_compare(t_moon *current, t_moon *orig)
{
/* 	printf("pos\n");
	printf("cur x %d | orig x %d\n", current->pos.x, orig->pos.x);
	printf("cur y %d | orig y %d\n", current->pos.y, orig->pos.y);
	printf("cur z %d | orig z %d\n", current->pos.z, orig->pos.z);
	printf("vel\n");
	printf("cur x %d | orig x %d\n", current->vel.x, orig->vel.x);
	printf("cur y %d | orig y %d\n", current->vel.y, orig->vel.y);
	printf("cur z %d | orig z %d\n", current->vel.z, orig->vel.z); */
	while (current)
	{
		if (current->pos.z != orig->pos.z)
			return (0);
/* 		if (current->pos.y != orig->pos.y)
			return (0);
		if (current->pos.z != orig->pos.z)
			return (0);
		if (current->vel.x != orig->vel.x)
			return (0);
		if (current->vel.y != orig->vel.y)
			return (0);
		if (current->vel.z != orig->vel.z)
			return (0);
		current = current->next;
		orig = orig->next;
	}
	return (1); */
		current = current->next;
		orig = orig->next;
	}
	return (1);
}

void	free_moons(t_moon *moons)
{
	t_moon *last;

	while (moons)
	{
		last = moons;
		moons = moons->next;
		free(last);
	}
}

t_moon	*time_skip(t_moon **moons)
{
	unsigned long	step;
	t_moon	*new;
	t_moon	*orig;
	t_moon	*newlst;
	t_moon	*olditer;
//	static int change = 0;

	step = 0;
	orig = moon_dup(*moons);
	newlst = NULL;
	while (1)
	{
		if (step)
			if (moon_compare(*moons, orig))
				break ;
		olditer = *moons;
		while (olditer)
		{
			new = update_moon(moons, olditer);
//			change = get_diff(new, olditer, change);
			moon_addbck(&newlst, new);
			olditer = olditer->next;
		}
		free_moons(*moons);
		*moons = newlst;
		newlst = NULL;
		step++;
	}
	print_moons(*moons);
	printf("\n");
	print_moons(orig);
	printf("steps %lu\n", step);
	free_moons(orig);
	return (*moons);
}

int		main(int argc, char **input)
{
	int fd;
	int		energy;
	t_moon	*moons;

//	if (argc < 2);
//		return (0);
	fd = open(input[1], O_RDONLY);
	moons = get_moons(fd);
//	print_moons(moons);
	time_skip(&moons);
	free_moons(moons);
//	energy = get_total_energy(moons);
//	printf("Total energy: %d\n");
	return (0);
}
