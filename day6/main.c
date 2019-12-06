/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 10:25:21 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/06 15:37:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day6.h"

t_planet	*get_planets(int fd)
{
	int			red;
	char		id[4];
	char		c;
	int			i;
	t_list		*storage;
	t_planet	*list;
	t_planet	*tmp;
	t_planet	*found;
	t_list		*lst;
	t_list		*child;

	storage = NULL;
	list = NULL;
	tmp = NULL;
	found = NULL;
	list = NULL;
	child = NULL;
	i = 0;
	red = read(fd, &c, 1);
	while (red > 0)
	{
		if (c == ')')
		{
			id[i] = 0;
//			tmp = find_pl(&list, id);
			tmp = find_l(storage, id);				//find the parent in the storage
			if (tmp == 0)							//if it doesnt exist in the storage <-
			{
				tmp = p_new(strdup(id));			//I make a new planet
				lst = lst_new(tmp);				//I make a new list containing the planet
				lst_addback(&storage, lst);			//I add the list to the end
//				if (list == NULL)					//If there is no list root yet, I turn this parent into the root.
//					list = tmp;
			}
//			printf("%s\n", id);
			i = 0;
		}
		else if (c == '\n')
		{
			id[i] = 0;
			found = find_l(storage, id); 			//find the child in the list (see if it exists)
//			if (found == list && list != NULL) 		//if the child I've found is the current start of the list
//				list = replace_root(&list, tmp); 	//then I replace the current root(the child) with the parent
			if (found == 0) 						//if I have not found the child (it doesnt exist yet)
			{
				found = p_new(strdup(id)); 			//then I make a new planet and a new list
				child = lst_new(found); 			//and make a new list, containing the new planet
				add_child(tmp, &found); //I add the child to its parent
				lst_addback(&storage, child); 		//and then I add the new list to the storage
//				lst_addback(&storage, lst);
			}
			else
				add_child(tmp, &found);				//if it does exist in the storage, I add it to its parent
//			printf("%s\n", id);
			i = 0;
		}
		else
		{
			id[i] = c;
			i++;
		}
		red = read(fd, &c, 1);
	}
//	print_ll(storage);
	list = find_l(storage, "COM");
	traverse_planets(list);
	return (list);
}

int			main(int argc, char **input)
{
	t_planet	*planets;
	int			fd;

	if (argc < 2)
		return (0);
	fd = open(input[1], O_RDONLY);
	planets = get_planets(fd);
//	print_planets(&planets);
//	traverse_planets(planets);
	return (0);
}
