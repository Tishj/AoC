/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_count.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 15:42:12 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/06 15:50:01 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day6.h"

int		count(t_planet *list)
{
	int res;

	res = 0;
	if (list == NULL)
		return (res);
	res = list->orbits;
	if (list->c1)
		res += count(list->c1);
	if (list->c2)
		res += count(list->c2);
	if (list->c3)
		res += count(list->c3);
	return (res);
}

t_planet	*find_unset(t_planet *list)
{
	t_planet	*res;

	res = NULL;
	if (list == NULL)
		return (res);
	if (list->orbits == -1)
		res = list;
	if (list->c1 && res == NULL)
		res = find_unset(list->c1);
	if (list->c2 && res == NULL)
		res = find_unset(list->c2);
	if (list->c3 && res == NULL)
		res = find_unset(list->c3);
	return (res);
}
