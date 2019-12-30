/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_list.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 15:40:19 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/29 15:40:19 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

t_list	*ft_lst_findn(t_list **head, int n)
{
	int i;
	t_list *iter;

	i = 0;
	iter = *head;
	while (iter)
	{
		if (i == n)
			return (iter);
		iter = iter->next;
		i++;
	}
	return (NULL);
}

void	ft_lst_addback(t_list **head, t_list *new)
{
	t_list *tmp;

	tmp = *head;
	if (!head)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_list	*ft_lst_new(t_coord pos)
{
	t_list *new;

	new = malloc(sizeof(t_list));
	new->pos = pos;
	new->next = NULL;
	return (new);
}
