/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day12.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 11:44:12 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/13 13:17:41 by tbruinem      ########   odam.nl         */
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
t_coord				reset_coords(void);
int					nb_flip(int orig);
t_moon				*moon_dup(t_moon *moons);
t_moon				*time_skip(t_moon **moons);
int					get_offset(int c1, int c2);
t_moon				*get_moons(int fd);
int					get_sum(t_moon *moons, char c);
int					get_total_energy(t_moon *moons);
int					get_planet_energy(t_coord pos, t_coord vel);
int					get_diff(t_moon *orig, t_moon *current, int diff);

#endif
