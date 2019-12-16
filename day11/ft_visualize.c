/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_visualize.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/15 13:12:58 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/15 13:12:58 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"

void	ft_put2darr(char **arr)
{
	int x;
	int y;

	y = 0;
	while (arr[y])
	{
		x = 0;
		while (arr[y][x])
		{
			printf("%c", arr[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

t_coord	ft_fieldsize(t_tile *lst)
{
	t_coord size;

	size.x = 0;
	size.y = 0;
	while (lst)
	{
		if (lst->coords.x > size.x)
			size.x = lst->coords.x;
		if (lst->coords.y > size.y)
			size.y = lst->coords.y;
		lst = lst->next;
	}
	return (size);
}

void	ft_makefield(t_tile **lst)
{
	t_tile		*tmp;
	char		**arr;
	t_coord	size;
	int			i;
	int			j;

	i = 0;
	size = ft_fieldsize(*lst);
	tmp = *lst;
	arr = (char **)malloc(sizeof(char *) * (size.y + 1));
	while (i < size.y)
	{
		j = 0;
		arr[i] = malloc(sizeof(char) * (size.x + 1));
		while (j < size.x)
		{
			arr[i][j] = '.';
			j++;
		}
		i++;
	}
	while (tmp)
	{
		if (tmp->color == 1)
			arr[tmp->coords.y][tmp->coords.x] = '#';
		tmp = tmp->next;
	}
	ft_put2darr(arr);
}
