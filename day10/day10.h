/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day10.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 11:44:12 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/10 18:58:24 by tbruinem      ########   odam.nl         */
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

int g_size = 0;

#endif
