/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/14 12:36:46 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/14 12:36:46 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"

void	ft_print_tile(t_tile *lst)
{
	while (lst)
	{
		printf("X %d | Y%d | Color : %d\n", lst->coords.x, lst->coords.y, lst->color);
		lst = lst->next;
	}
}

void	ft_print_arr(long *array, int len)
{
	int i;

	i = 0;
	while (i <= len)
	{
		printf("%4d | %ld\n", i, array[i]);
		i++;
	}
}
