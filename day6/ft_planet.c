/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_planet.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:32:24 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/06 15:00:23 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day6.h"

void		traverse_planets(t_planet *current)
{
	t_planet *tmp;

	tmp = current;
	if (current == 0)
		return ;
	printf("PLANET: %5s | ", current->id);
	if (current->c1)
		printf("c1: %5s | ", current->c1->id);
	if (current->c2)
		printf("c2: %5s | ", current->c2->id);
	if (current->c3)
		printf("c3: %5s | ", current->c3->id);
	printf("\n");
		traverse_planets(tmp->c1);
		traverse_planets(tmp->c2);
		traverse_planets(tmp->c3);
}

t_planet	*p_new(char *id)
{
	t_planet	*new;

	new = (t_planet *)malloc(sizeof(t_planet));
	if (new == NULL)
		return (NULL);
	new->id = id;
	new->c1 = NULL;
	new->c2 = NULL;
	new->c3 = NULL;
	new->orbits = -1;
	return (new);
}

void		add_child(t_planet **parent, t_planet *child)
{
	t_planet	*tmp;

	if (parent == NULL || (*parent) == NULL)
		return ;
//	printf("Parent: %5s | Child %5s\n", (*parent)->id, child->id);
	if ((*parent)->c1 == 0)
	{
		(*parent)->c1 = child;
		return ;
	}
	if ((*parent)->c2 == 0)
	{
		(*parent)->c2 = child;
		return ;
	}
	if ((*parent)->c3 == 0)
	{
		(*parent)->c3 = child;
		return ;
	}
}

t_planet	*replace_root(t_planet **list, t_planet *new)
{
	t_planet *tmp;

	tmp = *list;
	*list = new;
	add_child(list, tmp);
	return (*list);
}

t_planet	*find_pl(t_planet **list, char *to_find)
{
	t_planet *tmp;
	t_planet *res;

	res = NULL;
	tmp = *list;
	if (tmp == NULL)
		return (0);
	printf("cur: %5s | to_find: %5s\n", tmp->id, to_find);
	if (strcmp(tmp->id, to_find))
		return (tmp);
	if (tmp->c1 && res == NULL)
		res = find_pl(&(tmp->c1), to_find);
	if (tmp->c2 && res == NULL)
		res = find_pl(&(tmp->c2), to_find);
	if (tmp->c3 && res == NULL)
		res = find_pl(&(tmp->c3), to_find);
	return (res);
}
