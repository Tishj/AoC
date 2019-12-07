/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_valid.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/07 15:20:54 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/07 15:20:54 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day7.h"

int		match_counter(char *number, int start, int end)
{
	int res;
	char c;
	int i;
	int tmp;

	c = (start + '0');
	res = 6;
	while (c >= (start + '0') && c <= (end + '0'))
	{
		i = 0;
		tmp = 0;
		while (number[i])
		{
			if (number[i] == c)
				tmp++;
			i++;
		}
		if (tmp > 1)
			return (0);
		c++;
	}
	return (1);
}

int		is_possible(char *number, int start, int end)
{
	int i;

	i = 0;
	if (match_counter(number, start, end) == 0)
		return (0);
	i = 0;
	while (number[i])
	{
		if (number[i] >= (start + '0') && number[i] <= (end + '0'))
			i++;
		else
			return (0);
	}
	return (1);
}

int		get_valid(int number, int start, int end)
{
	char *tmp;
	int res;

	res = 0;
	while (number > 0)
	{
		tmp = ft_itoa(number);
		res = is_possible(tmp, start, end);
		if (res != 0)
			return (number);
		number--;
	}
	return (number);
}
