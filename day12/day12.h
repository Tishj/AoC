/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day12.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 11:44:12 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/12 14:42:30 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY12_H
# define DAY12_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>

typedef struct		s_coord
{
	int				x;
	int				y;
	int				z;
}					t_coord;

typedef struct		s_moon
{
	t_coord			pos;
	t_coord			vel;
	struct s_moon	*next;
}					t_moon;

t_moon				*moon_new(t_coord pos, t_coord vel);
void				moon_addbck(t_moon **start, t_moon *new);
t_moon				*init_moons(void);
void				print_moons(t_moon *moons);

#endif
