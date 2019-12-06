/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day6.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 10:20:09 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/06 10:20:09 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY6_H
# define DAY6_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>

typedef struct			s_planet
{
	char				*id;
	struct s_planet		*c1;
	struct s_planet		*c2;
	struct s_planet		*c3;
	int					orbits;
}						t_planet;

typedef struct			s_list
{
	struct s_planet		*planet;
	struct s_list		*next;
}						t_list;

void		print_ll(t_list *storage);
void		print_planets(t_planet **to_print);

t_list		*lst_new(t_planet **planet);
void		lst_addback(t_list **store, t_list *new);
t_planet	*find_l(t_list **store, char *id);

void		add_child(t_planet **parent, t_planet *child);
t_planet	*replace_root(t_planet **list, t_planet *new);
t_planet	*find_pl(t_planet **list, char *to_find);
t_planet	*p_new(char *id);
void		traverse_planets(t_planet *current);

#endif
