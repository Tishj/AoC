/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_valid.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/07 15:20:54 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/07 15:20:54 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"

int		ft_match_counter(char *start)
{
	int res;
	char c;
	int i;
	int tmp;

	c = '0';
	res = 6;
	while (c >= '0' && c <= '4')
	{
		i = 0;
		tmp = 0;
		while (start[i])
		{
			if (start[i] == c)
				tmp++;
			i++;
		}
		if (tmp > 1)
			return (0);
		c++;
	}
	return (1);
}

int		ft_is_possible(char *start)
{
	int i;

	i = 0;
	if (ft_match_counter(start) == 0)
		return (0);
	i = 0;
	while (start[i])
	{
		if (start[i] >= '0' && start[i] <= '4')
			i++;
		else
			return (0);
	}
	return (1);
}

int		ft_get_valid(int start)
{
	char *tmp;
	int res;

	res = 0;
	while (start > 0)
	{
		tmp = ft_itoa(start);
		res = ft_is_possible(tmp);
		if (res != 0)
			return (start);
		start--;
	}
	return (start);
}
