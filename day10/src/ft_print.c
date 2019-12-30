/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 23:17:30 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/10 23:17:30 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

void	print_array(char **array)
{
	int x;
	int y;

	y = 0;
	while (array[y])
	{
		x = 0;
		while (array[y][x])
		{
			if (array[y][x] == 'R')
			{
				printf("\033[1;31m");
				printf("D ");
				printf("\033[0m");
			}
			else if (array[y][x] == '.')
				printf("%c ", array[y][x]);
			else if (array[y][x] == 'D')
			{
				printf("\033[1;31m");
				printf("D ");
				printf("\033[0m");
			}
			else
				printf("%c ", array[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
//	printf("-------------------------------------------------------------------------\n");
}
