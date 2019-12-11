/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day10.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 11:44:12 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/11 14:25:24 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY10_H
# define DAY10_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>

char			*ft_itoa(int n);
int				get_valid(int start);

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_stepper
{
	t_coord			start;
	t_coord			step;
	t_coord			total;
}					t_stepper;

int					get_next_line(int fd, char **line);

int					is_it_safe(char **map, t_coord goal, int max_size);
int					get_total(char **map);
char				**get_array(int fd, int *max_size);
char				**dup_array(char **map);
void				print_array(char **array, t_coord coords);
int					get_div(t_coord course, int max_size);

#endif
