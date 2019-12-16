/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tile.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/14 14:37:41 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/14 14:37:41 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"

int			ft_tile_count(t_tile **lst)
{
	t_tile	*list;
	t_tile	*tmp;
	int size;

	list = *lst;
//	printf("counting tiles..\n");
	size = 0;
	while (list)
	{
		tmp = *lst;
		while (tmp)
		{
			if (tmp != list)
				if (tmp->coords.x == list->coords.x && tmp->coords.y == list->coords.y)
					break ;
			tmp = tmp->next;
		}
		if (!tmp)
			size++;
		list = list->next;
	}
	return (size);
}

void		ft_tile_addbck(t_tile **list, t_tile *new)
{
	t_tile	*iter;

	if (*list == NULL)
	{
		*list = new;
		return;
	}
	iter = *list;
	while (iter->next)
		iter = iter->next;
	iter->next = new;
}

t_tile		*ft_tile_new(t_coord coords, int color)
{
	t_tile *new;

	new = malloc(sizeof(t_tile));
	new->color = color;
	new->coords = coords;
	new->next = NULL;
	return (new);
}

t_tile	*ft_tile_find(t_tile **list, t_coord coords)
{
	t_tile	*lst;

	lst = *list;
	while (lst)
	{
		if (ft_coordcmp(coords, lst->coords))
		{
//			printf("Found a match!\n");
			return (lst);
		}
		lst = lst->next;
	}
	return (NULL);
}
