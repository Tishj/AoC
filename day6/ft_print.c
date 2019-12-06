/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:29:12 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/06 15:20:31 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day6.h"

void		print_ll(t_list *storage)
{
	printf("List:\n");
	while (storage)
	{
		printf("P: %5s | ", storage->planet->id);
		if (storage->planet->c1)
			printf("C1: %5s | ", storage->planet->c1->id);
		if (storage->planet->c2)
			printf("C2 :%5s | ", storage->planet->c2->id);
		if (storage->planet->c3)
			printf("C3 :%5s | ", storage->planet->c3->id);
		printf("\n");
		storage = storage->next;
	}
}

void		print_planets(t_planet **to_print)
{
	t_planet	*tmp;

	tmp = *to_print;
//	if (tmp == NULL)
//		return ;
	printf("PLANET: %5s | ", tmp->id);
	if (tmp->c1)
		printf("c1: %5s | ", tmp->c1->id);
	else
		printf("c1: %5s | ", "no");
	if (tmp->c2)
		printf("c2: %5s | ", tmp->c2->id);
	else
		printf("c2: %5s | ", "no");
	if (tmp->c2)
		printf("c3: %5s | ", tmp->c3->id);
	else
		printf("c2: %5s | ", "no");
	printf("\n");
	if (tmp->c1)
		print_planets(&(tmp->c1));
	if (tmp->c2)
		print_planets(&(tmp->c2));
	if (tmp->c3)
		print_planets(&(tmp->c3));
}
