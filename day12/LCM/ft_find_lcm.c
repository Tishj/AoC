/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_find_lcm.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/14 21:40:39 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/14 21:40:39 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct		s_coord
{
	int				x;
	int				y;
	int				z;
}					t_coord;

unsigned long	ft_lcm(unsigned long a, unsigned long b)
{
	unsigned long tmp;

	tmp = a;
	while (1)
	{
		if (tmp % a == 0 && tmp % b == 0)
			break;
		tmp += a;
	}
	return (tmp);
}

unsigned long	ft_get_lcm(t_coord new)
{
	unsigned long tmp;
	unsigned long lcm;

	if(new.x<new.y) 
		tmp = ft_lcm(new.x,new.y);
	else
		tmp = ft_lcm(new.y,new.x);
	if(tmp>new.z)
		lcm = ft_lcm(tmp,new.z);
	else
		lcm = ft_lcm(new.z,tmp);
	printf("LCM of %d|%d|%d = %lu\n", new.x, new.y, new.z, lcm);
	return (0);
}
