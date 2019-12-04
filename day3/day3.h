/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   day3.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 13:38:52 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/04 19:31:55 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DAY3_H
# define DAY3_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>

typedef struct			s_coords
{
	int					x;
	int					y;
	struct s_coords		*next;
}						t_coords;

typedef struct			s_collision
{
	int					distance;
	struct s_collision	*next;
}						t_collision;

typedef struct			s_move
{
	int					amount;
	char				direction;
}						t_move;

#endif
