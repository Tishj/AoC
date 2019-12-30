/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_main_part2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 12:34:32 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/29 12:34:32 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

int		main(int argc, char **input)
{
	int fd;
	char **map;
	char **dup;
	int max_size;
	t_coord pos;

	if (argc != 2)
		return (0);
	fd = open(input[1], O_RDONLY);
	map = ft_map_get(fd, &max_size);
	ft_asteroid_vaporizer(map, max_size);
	return (0);
}
