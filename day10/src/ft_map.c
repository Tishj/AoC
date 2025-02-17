/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_map.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 12:30:38 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/29 12:30:38 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

char	**ft_map_dup(char **map)
{
	int		y;
	int		x;
	char	**dup;

	y = 0;
	dup = malloc(sizeof(char *) * (39 + 1));
	while (map[y])
	{
		x = 0;
		dup[y] = malloc(sizeof(char) * (39 + 1));
		while (map[y][x])
		{
			dup[y][x] = map[y][x];
			x++;
		}
		dup[y][x] = 0;
		y++;
	}
	dup[y] = 0;
	return (dup);
}

char	**ft_map_get(int fd, int *max_size)
{
	int		red;
	char	c;
	char	**array;
	char	*firstline;
	int		i;

	i = 0;
	get_next_line(fd, &firstline);
	*max_size = strlen(firstline);
	array = malloc(sizeof(char *) * (*max_size + 1));
	array[i] = firstline;
	i++;
	while (i < *max_size)
	{
		get_next_line(fd, &array[i]);
		i++;
	}
	array[i] = 0;
	return (array);
}
