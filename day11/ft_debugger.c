/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_debugger.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 15:30:50 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/13 15:30:50 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"

void	ft_debug(char c, int i, long *array, long p1, long p2)
{
/* 	if (c == '+')
		printf("%-6d | %-16ld,%-16ld,%-16ld,%-16ld | %-8ld + %-8ld = %-8ld\n", i, array[i], array[i + 1], array[i + 2], array[i + 3], p1, p2, array[array[i + 3]]);
	if (c == '*')
		printf("%-6d | %-16ld,%-16ld,%-16ld,%-16ld | %-8ld * %-8ld = %-8ld\n", i, array[i], array[i + 1], array[i + 2], array[i + 3], p1, p2, array[array[i + 3]]);
	if (c == 'i')
		printf("%-6d | %-16ld,%-16ld                                   | %-8ld = %-8ld\n", i, array[i], array[i + 1], p1, array[array[i + 1]]); */
	/* if (c == 'o')
		printf("%-6d | %-16ld,%-16ld                                   | %-8ld printed\n", i, array[i], array[i + 1], p1); */
	/* if (c == '<')
		printf("%-6d | %-16ld,%-16ld,%-16ld                  | %-8ld < %-8ld? %-8ld\n", i, array[i], array[i + 1], array[i + 2], p1, p2, array[array[i + 2]]);
	if (c == 't')
		printf("%-6d | %-16ld,%-16ld                                   | %-8ld (== 1)? jump %-8ld\n", i, array[i], array[i + 1], p1, array[i + 2]);
	if (c == 'f')
		printf("%-6d | %-16ld,%-16ld                                   | %-8ld (== 0)? jump %-8ld\n", i, array[i], array[i + 1], p1, array[i + 2]);
	if (c == '=')
		printf("%-6d | %-16ld,%-16ld,%-16ld                  | %-8ld == %-8ld? %-8ld\n", i, array[i], array[i + 1], array[i + 2], p1, p2, array[array[i + 2]]);
	if (c == 'r')
		printf("%-6d | %-16ld,%-16ld                                   | %-8ld + %-8ld = %-8ld relative base\n", i, array[i], array[i + 1], p2 - p1, p1, p2); */
}

