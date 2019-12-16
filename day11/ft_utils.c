/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/14 12:35:37 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/14 12:35:37 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"

int		ft_coordcmp(t_coord c1, t_coord c2)
{
	if (c1.x != c2.x)
		return (0);
	if (c1.y != c2.y)
		return (0);
	return (1);
}

t_inst	get_inst(long in)
{
	t_inst instruct;
	int mod;

	mod = (int)in;

	instruct.color = ft_mod(&mod);
	instruct.direction = ft_mod(&mod);
	return (instruct);
}

t_coord	reset_coord(void)
{
	t_coord new;

	new.x = 0;
	new.y = 0;
	return (new);
}

long	*ft_arrdup(long *org, int len)
{
	int i;
	long *new;

	new = malloc(sizeof(int) * (len + 1));
	i = 0;
	while (i < len)
	{
		new[i] = org[i];
		i++;
	}
	return (new);
}

int		ft_mod(int *value)
{
	int res;

	res = *value % 10;
	*value = *value / 10;
	return (res);
}

long	ft_get_value(int *code, long *array, int index, int *rbase)
{
	int pos;
	int mod;

	mod = ft_mod(code);
//	printf("%-6d | mod: %d | rbase: %d | array[rbase + index] = %-16ld\n", index - 1, mod, *rbase, array[*rbase + index]);
	pos = array[index];
	if (mod == 0)
		return (array[pos]);
	else if (mod == 1)
		return (array[index]);
	else if (mod == 2)
		return (array[array[index] + *rbase]);
}
