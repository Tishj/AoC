/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 20:01:13 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/14 14:58:15 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"


long	*ft_get_array(int fd, int len)
{
	long	*new;
	int		i;
	int		red;
	char	c;
	long 	res;
	int n;

	n = 1;
	new = malloc(sizeof(long) * (len + 1));
	red = read(fd, &c, 1);
	i = 0;
	res = 0;
	while (red > 0)
	{
//		printf("%c\n", c);
		if (c == '-')
			n = -1;
		if (c >= '0' && c <= '9')
			res = res * 10 + (c - '0');
		if (c == ',' || c == '\n')
		{
			new[i] = (res * n);
			res = 0;
			n = 1;
			i++;
		}
		red = read(fd, &c, 1);
	}
	while (i <= len)
	{
		new[i] = 0;
		i++;
	}
	return (new);
}

int		main(int argc, char **input)
{
	int fd;
	long *org;
	int	tiles;

	if (argc < 2)
		return (0);
	fd = open(input[1], O_RDONLY);
	org = ft_get_array(fd, 2000);
	tiles = ft_hull_painter(org);
	printf("tiles painted: %d\n", tiles);
//	ft_print_arr(org, 100);
//	max_signal = ft_input_iter(99999, org);
//	max_signal = ft_intcode(org, 0, '1');
//	ft_print_arr(org, 100);
//	printf("BOOST: %ld\n", max_signal);
	return (0);
}
