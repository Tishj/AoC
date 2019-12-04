/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 23:10:10 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/04 23:10:10 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day1.h"

int		main(int argc, char **input)
{
	int fd;
	int res;
	int red;
	char c;
	int final;

	if (argc > 1)
		fd = open(input[1], O_RDONLY);
	res = 0;
	final = 0;
	red = read(fd, &c, 1);
	while (red > 0)
	{
		if (c == '\n')
		{
			while (res > 0)
			{
				printf("result: %d | (%d / 3) - 2\n", (res / 3) - 2, res);
				res = (res / 3) - 2;
				if (res < 0)
					res = 0;
				final += res;
			}
			res = 0;
		}
		if (c >= '0' && c <= '9')
		{
			res = res * 10 + (c - '0');
//			printf("%d\n", res);
		}
		red = read(fd, &c, 1);
	}
	printf("%d\n", final);
	return (0);
}
