/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day11.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 10:28:41 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/15 13:43:55 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY11_H
# define DAY11_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>

typedef struct			s_coord
{
	int					x;
	int					y;
}						t_coord;

typedef struct			s_tile
{
	int					color;
	struct s_coord		coords;
	struct s_tile		*next;
}						t_tile;


typedef	struct			s_inst
{
	int					direction;
	int					color;
}						t_inst;

long			ft_intcode(long *array, long output, char setting);
long			*ft_arrdup(long *org, int len);
char			*ft_itoa(int n);
int             ft_get_valid(int start);
int             ft_input_iter(int input, long *orig);
int             ft_is_possible(char *start);
int             ft_match_counter(char *start);
int             ft_mod(int *value);
int             ft_phase_iter(long *orig, char *sequence);
void    		ft_debug(char c, int i, long *array, long p1, long p2);
long			ft_do_op(long *array, int *i, long *output, int *start, char setting, int *rbase);
void    		ft_do_add(long *array, int *index, int *code, int *rbase);
void			ft_do_add(long *array, int *index, int *code, int *rbase);
void    		ft_do_comp(long *array, int *index, int *code, int op, int *rbase);
void    		ft_do_comp(long *array, int *index, int *code, int op, int *rbase);
void    		ft_do_jump(long *array, int *index, int *code, int op, int *rbase);
void    		ft_do_jump(long *array, int *index, int *code, int op, int *rbase);
void   			ft_do_mul(long *array, int *index, int *code, int *rbase);
void    		ft_do_mul(long *array, int *index, int *code, int *rbase);
void    		ft_do_rbase(long *array, int *index, int *code, int op, int *rbase);
void    		ft_do_rbase(long *array, int *index, int *code, int op, int *rbase);
void    		ft_do_set(long *array, int *index, int *code, char setting,
				int *start, long output, int *rbase);
void    		ft_print_arr(long *array, int len);
long			ft_get_value(int *code, long *array, int index, int *rbase);
long			ft_do_prnt(long *array, int *index, long *out, int *code, int *rbase);

void		ft_tile_addbck(t_tile **list, t_tile *new);
int			ft_tile_count(t_tile **lst);
t_tile		*ft_tile_new(t_coord coords, int color);
int			ft_hull_painter(long *input);
t_coord		ft_turn(int dir, t_coord old, int steps);
int			ft_coordcmp(t_coord c1, t_coord c2);
t_coord		reset_coord(void);
t_inst		get_inst(long in);
t_tile		*ft_tile_find(t_tile **lst, t_coord coords);

void		ft_put2darr(char **arr);
t_coord		ft_fieldsize(t_tile *lst);
void		ft_makefield(t_tile **lst);

void		ft_print_tile(t_tile *lst);

#endif
