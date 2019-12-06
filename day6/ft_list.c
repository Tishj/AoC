/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_list.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:30:08 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/06 13:41:56 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day6.h"

t_list		*lst_new(t_planet **planet)
{
	t_list *new;

	new = malloc(sizeof(t_list));
	new->next = NULL;
	new->planet = *planet;
	return (new);
}

void	lst_addback(t_list **store, t_list *new)
{
	t_list	*lst;
	t_list	*prev;

	lst = *store;
	if (lst == NULL)
	{
		*store = new;
		return ;
	}
	while (lst)
	{
		prev = lst;
		lst = lst->next;
	}
	prev->next = new;
}

t_planet	*find_l(t_list **store, char *id)
{
	t_list *tmp;

	tmp = *store;
	while (tmp)
	{
//		printf("what am I even looking for? | current: %5s | to_find: %5s\n", tmp->planet->id, id);
		if (tmp->planet)
			if (strcmp(tmp->planet->id, id) == 0)
				return (tmp->planet);
		tmp = tmp->next;
	}
	return (NULL);
}
