/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day10.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 11:44:12 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/29 17:21:53 by tbruinem      ########   odam.nl         */
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

typedef struct		s_fcoord
{
	float			x;
	float			y;
}					t_fcoord;

typedef struct		s_list
{
	t_coord			pos;
	struct s_list	*next;
}					t_list;

typedef struct		s_ray
{
	t_fcoord		stp;
	t_fcoord		ttl;
	t_coord			pos;
}					t_ray;

typedef struct		s_stepper
{
	t_coord			start;
	t_coord			step;
	t_coord			total;
}					t_stepper;

enum direction
{
	Q_TOPRIGHT,
	Q_BOTRIGHT,
	Q_BOTLEFT,
	Q_TOPLEFT
};

int			get_next_line(int fd, char **line);
int			is_it_safe(char **map, t_coord goal, int max_size);
int			nb_flip(int nb);
int			get_div(t_coord course, int max_size);

t_ray		ft_ray_init(t_coord pos, t_fcoord step);

int			ft_asteroid_count(char **map);
void		ft_asteroid_vaporizer(char **map, int max_size);
void		ft_asteroid_find(char **map, t_coord start, int max_size);
void		ft_asteroid_scout(char **map, t_stepper data, int max_size);
void		ft_asteroid_del(char **map, t_ray ray, t_coord old, int max_size);

t_fcoord	ft_fcoord_init(float x, float y);

t_coord		ft_coord_init(int x, int y);

char		**ft_map_get(int fd, int *max_size);
char		**ft_map_dup(char **map);

void		print_array(char **array);
t_fcoord	ft_direction_translate(int dir, t_fcoord orig);
int			ft_direction_get(t_fcoord step, int cycle);

t_coord		smallest_step(t_coord orig);
t_coord		set_course(t_stepper data, int max_size);

#endif
