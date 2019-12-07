/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 20:01:13 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/05 20:01:13 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day7.h"

void	debug_me(char c, int i, int *array, int p1, int p2)
{
	if (c == '+')
		printf("%-6d | %-6d,%-6d,%-6d,%-4d | %-8d + %-8d = %-8d\n", i, array[i], array[i + 1], array[i + 2], array[i + 3], p1, p2, array[array[i + 3]]);
	if (c == '*')
		printf("%-6d | %-6d,%-6d,%-6d,%-4d | %-8d * %-8d = %-8d\n", i, array[i], array[i + 1], array[i + 2], array[i + 3], p1, p2, array[array[i + 3]]);
	if (c == '=')
		printf("%-6d | %-6d,%-6d             | %-8d = %-8d\n", i, array[i], array[i + 1], p1, array[array[i + 1]]);
}

void	print_array(int *array, int len)
{
	int i;

	i = 0;
	while (i <= len)
	{
		printf("%d\n", array[i]);
		i++;
	}
}

int		*get_array(int fd, int len)
{
	int		*new;
	int		i;
	int		red;
	char	c;
	int 	res;
	int n;

	n = 1;
	new = malloc(sizeof(int) * (len + 1));
	red = read(fd, &c, 1);
	i = 0;
	res = 0;
	while (i <= len)
	{
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
	return (new);
}

int		get_mod(int *value)
{
	int res;

	res = *value % 10;
	*value = *value / 10;
	return (res);
}

int		get_value(int *code, int *array, int index)
{
	int pos;

	pos = array[index];
	if (get_mod(code) == 0)
		return (array[pos]);
	else
		return (array[index]);
}

int		do_add(int *array, int *index, int *code)
{
	int p1;
	int p2;
	int pos;

	pos = array[(*index) + 3];
	p1 = get_value(code, array, (*index) + 1);
	p2 = get_value(code, array, (*index) + 2);
	array[pos] = p1 + p2;
	*index = (*index) + 4;
}

int		do_mul(int *array, int *index, int *code)
{
	int p1;
	int p2;
	int pos;

	pos = array[(*index) + 3];
	p1 = get_value(code, array, (*index) + 1);
	p2 = get_value(code, array, (*index) + 2);
	array[pos] = p1 * p2;
	*index = (*index) + 4;
}

int		do_set(int *array, int *index, int *code, char setting, int *start, int output)
{
	int p1;
	int pos;

	pos = array[(*index) + 1];
	p1 = output;
	if (*start == 1)
		p1 = (setting - '0');
	array[pos] = p1;
	*start = 0;
	*index = (*index) + 2;
}

int		do_prnt(int *array, int *index, int *code, int output)
{
	int p1;
	int pos;

	pos = array[(*index) + 1];
	p1 = get_value(code, array, (*index) + 1);
	output = p1;
//	printf("output signal: %d\n", output);
	*index = (*index) + 2;
	return (output);
}

void	do_jump(int *array, int *index, int *code, int op)
{
	int p1;
	int p2;
	int pos;

	p1 = get_value(code, array, (*index) + 1);
	p2 = get_value(code, array, (*index) + 2);
	if (p1 != 0 && op == 5)
		(*index) = p2;
	else if (p1 == 0 && op == 6)
		(*index) = p2;
	else
		(*index) = (*index) + 3;
}

int		do_comp(int *array, int *index, int *code, int op)
{
	int p1;
	int p2;
	int pos;

	pos = array[(*index) + 3];
	p1 = get_value(code, array, (*index) + 1);
	p2 = get_value(code, array, (*index) + 2);
	if (p1 < p2 && op == 7)
		array[pos] = 1;
	else if (p1 == p2 && op == 8)
		array[pos] = 1;
	else
		array[pos] = 0;
	*index = (*index) + 4;
}

int		do_op(int *array, int *i, int output, int *start, char setting)
{
	int op;
	int code;

	code = array[*i];
	op = get_mod(&code);
	if (get_mod(&code) != 0 || (op < 1 || 8 < op))
	{
		*i = *i + 1;
		return (output);
	}
	if (op == 1)
		(do_add(array, i, &code));
	if (op == 2)
		(do_mul(array, i, &code));
	if (op == 3)
		(do_set(array, i, &code, setting, start, output));
	if (op == 4)
		output = do_prnt(array, i, &code, output);
	if (op == 5)
		(do_jump(array, i, &code, op));
	if (op == 6)
		(do_jump(array, i, &code, op));
	if (op == 7)
		(do_comp(array, i, &code, op));
	if (op == 8)
		(do_comp(array, i, &code, op));
	return (output);
}

int		*array_dup(int *org, int len)
{
	int i;
	int *new;

	new = malloc(sizeof(int) * (len + 1));

	i = 0;
	while (i < len)
	{
		new[i] = org[i];
		i++;
	}
	return (new);
}

int		intcode(int *i, int *array, int output, char setting, int *start, int *phase, int *loop)
{
	int old_out;

	old_out = output;
	while (array[*i] != 99)
	{
		output = do_op(array, i, output, start, setting);
		if (old_out != output)
			break ;
	}
	if (*phase == 4 && array[*i] == 99)
		*loop = 0;
	return (output);
}

void	free_arrays(int **arrays)
{
	int i;

	i = 0;
	while (arrays[i])
	{
		free(arrays[i]);
		i++;
	}
}

int		phase_iterator(int *orig, char *sequence)
{
	int phase;
	int *dup;
	int output;
	int loop;
	int *storage[5];
	int counters[5];
	int start[5];

	start[0] = 1;
	start[1] = 1;
	start[2] = 1;
	start[3] = 1;
	start[4] = 1;
	counters[0] = 0;
	counters[1] = 0;
	counters[2] = 0;
	counters[3] = 0;
	counters[4] = 0;
	storage[0] = array_dup(orig, 506);
	storage[1] = array_dup(orig, 506);
	storage[2] = array_dup(orig, 506);
	storage[3] = array_dup(orig, 506);
	storage[4] = array_dup(orig, 506);
	loop = 1;
	output = 0;
	phase = 0;
	while (phase < 5)
	{
		printf("loop: %d | phase: %d | cur start: %d | cur index: %d | output: %d\n", loop, phase, start[phase], counters[phase], output);
		output = intcode(counters + phase, storage[phase], output, sequence[phase], start + phase, &phase, &loop);
		phase++;
		if (phase == 5 && loop == 1)
			phase = 0;
	}
	return (output);
}

int		input_iterator(int input, int *orig)
{
	int phase;
	int max_signal;
	char *sequence;
	int output;

//	input = 98765;
	max_signal = 0;
	input = get_valid(input, 5, 9);
	while (input > 0)
	{
		sequence = ft_itoa(input);
		output = phase_iterator(orig, sequence);
		if (output > max_signal)
			max_signal = output;
		printf("SEQUENCE: %s | signal generated: %d\n", sequence, output);
		input = get_valid(input - 1, 5, 9);
	}
	return (max_signal);
}

int		main(int argc, char **input)
{
	int fd;
	int *org;
	int max_signal;

	if (argc < 2)
		return (0);
	fd = open(input[1], O_RDONLY);
	org = get_array(fd, 506);
	max_signal = input_iterator(99999, org);
	printf("MAX SIGNAL: %d\n", max_signal);
	return (0);
}
