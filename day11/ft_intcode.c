/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intcode.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/14 12:37:55 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/14 12:37:55 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"

long	ft_intcode(long *array, long output, char setting)
{
	static int	i = 0;
	static int	start = 1;
	static int	rbase = 0;
	int			out;

	out = 0;
	while (array[i] != 99)
	{
//		printf("index: %d | %-6ld\n", i, array[i]);
		out = ft_do_op(array, &i, &output, &start, setting, &rbase);
		if (out == 1);
			break ;
	}
	if (array[i] == 99)
		return (-1);
	return (output);
}

int		ft_phase_iter(long *orig, char *sequence)
{
	int		phase;
	long	*dup;
	int		output;

	output = 0;
	phase = 0;
	while (phase < 5)
	{
		dup = ft_arrdup(orig, 506);
		output = ft_intcode(dup, output, *(sequence + phase));
		phase++;
		free(dup);
	}
	return (output);
}

int		ft_input_iter(int input, long *orig)
{
	int phase;
	int max_signal;
	char *sequence;
	int output;

	max_signal = 0;
	input = ft_get_valid(input);
	while (input > 0)
	{
		sequence = ft_itoa(input);
		output = ft_phase_iter(orig, sequence);
		if (output > max_signal)
			max_signal = output;
		printf("SEQUENCE: %s | signal generated: %d\n", sequence, output);
		input = ft_get_valid(input - 1);
	}
	return (max_signal);
}
