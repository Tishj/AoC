/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_moon_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/12 11:22:01 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/13 12:55:07 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day12.h"

t_moon	*moon_dup(t_moon *moons)
{
	t_moon *dup;
	t_moon *current;

	dup = NULL;
	while (moons)
	{
		current = moon_new(moons->pos, moons->vel);
		moon_addbck(&dup, current);
		moons = moons->next;
	}
	return (dup);
}

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

t_moon	*get_moons(int fd)
{
	int red;
	int ret;
	t_moon	*lst;
	t_moon	*new;
	t_coord	pos;
	t_coord vel;
	char	c;
	char	axis;
	int		n;

	ret = 0;
	n = 1;
	lst = NULL;
	vel = reset_coords();
	red = read(fd, &c, 1);
	while (red > 0)
	{
//		printf("%c\n", c);
		if (c == '\n')
		{
			new = moon_new(pos, vel);
			moon_addbck(&lst, new);
		}
		if (c == 'x' || (c == 'y' || c == 'z'))
			axis = c;
		if (c == ',' || c == '>')
		{
			if (axis == 'x')
				pos.x = ret * n;
			if (axis == 'y')
				pos.y = ret * n;
			if (axis == 'z')
				pos.z = ret * n;
			ret = 0;
			n = 1;
		}
		if (c == '-')
			n = -1;
		if (c >= '0' && c <= '9')
			ret = ret * 10 + (c - '0');
		red = read(fd, &c, 1);
	}
	return (lst);
}
