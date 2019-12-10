/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 20:01:13 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/10 00:03:55 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day9.h"

void	debug_me(char c, int i, long *array, long p1, long p2)
{
	if (c == '+')
		printf("%-6d | %-16ld,%-16ld,%-16ld,%-16ld | %-8ld + %-8ld = %-8ld\n", i, array[i], array[i + 1], array[i + 2], array[i + 3], p1, p2, array[array[i + 3]]);
	if (c == '*')
		printf("%-6d | %-16ld,%-16ld,%-16ld,%-16ld | %-8ld * %-8ld = %-8ld\n", i, array[i], array[i + 1], array[i + 2], array[i + 3], p1, p2, array[array[i + 3]]);
	if (c == 'i')
		printf("%-6d | %-16ld,%-16ld                                   | %-8ld = %-8ld\n", i, array[i], array[i + 1], p1, array[array[i + 1]]);
	if (c == 'o')
		printf("%-6d | %-16ld,%-16ld                                   | %-8ld printed\n", i, array[i], array[i + 1], p1);
	if (c == '<')
		printf("%-6d | %-16ld,%-16ld,%-16ld                  | %-8ld < %-8ld? %-8ld\n", i, array[i], array[i + 1], array[i + 2], p1, p2, array[array[i + 2]]);
	if (c == 't')
		printf("%-6d | %-16ld,%-16ld                                   | %-8ld (== 1)? jump %-8ld\n", i, array[i], array[i + 1], p1, array[i + 2]);
	if (c == 'f')
		printf("%-6d | %-16ld,%-16ld                                   | %-8ld (== 0)? jump %-8ld\n", i, array[i], array[i + 1], p1, array[i + 2]);
	if (c == '=')
		printf("%-6d | %-16ld,%-16ld,%-16ld                  | %-8ld == %-8ld? %-8ld\n", i, array[i], array[i + 1], array[i + 2], p1, p2, array[array[i + 2]]);
	if (c == 'r')
		printf("%-6d | %-16ld,%-16ld                                   | %-8ld + %-8ld = %-8ld relative base\n", i, array[i], array[i + 1], p2 - p1, p1, p2);
}

void	print_array(long *array, int len)
{
	int i;

	i = 0;
	while (i <= len)
	{
		printf("%4d | %ld\n", i, array[i]);
		i++;
	}
}

long	*get_array(int fd, int len)
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

int		get_mod(int *value)
{
	int res;

	res = *value % 10;
	*value = *value / 10;
	return (res);
}

long	get_value(int *code, long *array, int index, int *rbase)
{
	int pos;
	int mod;

	mod = get_mod(code);
//	printf("%-6d | mod: %d | rbase: %d | array[rbase + index] = %-16ld\n", index - 1, mod, *rbase, array[*rbase + index]);
	pos = array[index];
	if (mod == 0)
		return (array[pos]);
	else if (mod == 1)
		return (array[index]);
	else if (mod == 2)
		return (array[array[index] + *rbase]);
}

void	do_add(long *array, int *index, int *code, int *rbase)
{
	long p1;
	long p2;
	int pos;
	int posmode;

	p1 = get_value(code, array, (*index) + 1, rbase);
	p2 = get_value(code, array, (*index) + 2, rbase);
	posmode = get_mod(code);
	if (posmode == 0)
		pos = array[*index + 3];
	if (posmode == 1)
		pos = *index + 3;
	if (posmode == 2)
		pos = array[*index + 3] + *rbase;
	array[pos] = p1 + p2;
	debug_me('+', *index, array, p1, p2);
	*index = (*index) + 4;
}

void	do_mul(long *array, int *index, int *code, int *rbase)
{
	long p1;
	long p2;
	int pos;
	int posmode;

	p1 = get_value(code, array, (*index) + 1, rbase);
	p2 = get_value(code, array, (*index) + 2, rbase);
	posmode = get_mod(code);
	if (posmode == 0)
		pos = array[*index + 3];
	if (posmode == 1)
		pos = *index + 3;
	if (posmode == 2)
		pos = array[*index + 3] + *rbase;
	array[pos] = p1 * p2;
	debug_me('*', *index, array, p1, p2);
	*index = (*index) + 4;
}

void	do_set(long *array, int *index, int *code, char setting,
		int *start, long output, int *rbase)
{
	long p1;
	int pos;
	int posmode;

	p1 = get_value(code, array, (*index) + 1, rbase);
	posmode = get_mod(code);
	if (posmode == 0)
		pos = array[*index + 3];
	if (posmode == 1)
		pos = *index + 3;
	if (posmode == 2)
		pos = array[*index + 3] + *rbase;
	if (*start == 1)
		p1 = (setting - '0');
	array[pos] = p1;
	*start = 0;
	debug_me('i', *index, array, p1, 0);
	*index = (*index) + 2;
}

long	do_prnt(long *array, int *index, int *code, int *rbase)
{
	long p1;

	p1 = get_value(code, array, (*index) + 1, rbase);
//	printf("output signal: %ld\n", p1);
	*index = (*index) + 2;
	debug_me('o', *index, array, p1, 0);
	return (p1);
}

void	do_jump(long *array, int *index, int *code, int op, int *rbase)
{
	long p1;
	long p2;
//	int pos;
//	int posmode;

	p1 = get_value(code, array, (*index) + 1, rbase);
	p2 = get_value(code, array, (*index) + 2, rbase);
/* 	if (posmode == 0)
		pos = array[*index + 3];
	if (posmode == 1)
		pos = *index + 3;
	if (posmode == 2) */
	if (p1 != 0 && op == 5)
	{
		(*index) = p2;
		debug_me('t', *index, array, p1, p2);
	}
	else if (p1 == 0 && op == 6)
	{
		(*index) = p2;
		debug_me('f', *index, array, p1, p2);
	}
	else
		(*index) = (*index) + 3;
}

void	do_comp(long *array, int *index, int *code, int op, int *rbase)
{
	long p1;
	long p2;
	int pos;
	int posmode;

	p1 = get_value(code, array, (*index) + 1, rbase);
	p2 = get_value(code, array, (*index) + 2, rbase);
	posmode = get_mod(code);
	if (posmode == 0)
		pos = array[*index + 3];
	if (posmode == 1)
		pos = *index + 3;
	if (posmode == 2)
		pos = array[*index + 3] + *rbase;
	if (p1 < p2 && op == 7)
	{
		array[pos] = 1;
		debug_me('<', *index, array, p1, p2);
	}
	else if (p1 == p2 && op == 8)
	{
		array[pos] = 1;
		debug_me('=', *index, array, p1, p2);
	}
	else
		array[pos] = 0;
	*index = (*index) + 4;
}

void	do_rbase(long *array, int *index, int *code, int op, int *rbase)
{
	long p1;

	p1 = get_value(code, array, (*index) + 1, rbase);
//	printf("index: %d | rbase: %d | to add: %ld | from index: %d\n", *index, *rbase, p1, *index + *rbase);
	*rbase = *rbase + p1;
	debug_me('r', *index, array, p1, *rbase);
	*index = (*index) + 2;
}


long	do_op(long *array, int *i, long output, int *start, char setting, int *rbase)
{
	int op;
	int code;

	code = array[*i];
	op = get_mod(&code);
	if (get_mod(&code) != 0 || (op < 1 || 9 < op))
	{
		*i = *i + 1;
		return (output);
	}
//	printf("code :%d | op: %d\n", code, op);
	if (op == 1)
		(do_add(array, i, &code, rbase));
	if (op == 2)
		(do_mul(array, i, &code, rbase));
	if (op == 3)
		(do_set(array, i, &code, setting, start, output, rbase));
	if (op == 4)
		output = do_prnt(array, i, &code, rbase);
	if (op == 5)
		(do_jump(array, i, &code, op, rbase));
	if (op == 6)
		(do_jump(array, i, &code, op, rbase));
	if (op == 7)
		(do_comp(array, i, &code, op, rbase));
	if (op == 8)
		(do_comp(array, i, &code, op, rbase));
	if (op == 9)
		(do_rbase(array, i, &code, op, rbase));
//	printf("I stopped working\n");
	return (output);
}

long	*array_dup(long *org, int len)
{
	int i;
	long *new;

	new = malloc(sizeof(int) * (len + 1));
	i = 0;
	while (i < len)
	{
		new[i] = org[i];
		i++;
	}
	return (new);
}

long	intcode(long *array, long output, char setting)
{
	int i;
	int start;
	int rbase;

	rbase = 0;
	start = 1;
	i = 0;
	while (array[i] != 99)
	{
//		printf("index: %d | %-6ld\n", i, array[i]);
		output = do_op(array, &i, output, &start, setting, &rbase);
	}
	return (output);
}

int		phase_iterator(long *orig, char *sequence)
{
	int		phase;
	long	*dup;
	int		output;

	output = 0;
	phase = 0;
	while (phase < 5)
	{
		dup = array_dup(orig, 506);
		output = intcode(dup, output, *(sequence + phase));
		phase++;
		free(dup);
	}
	return (output);
}

int		input_iterator(int input, long *orig)
{
	int phase;
	int max_signal;
	char *sequence;
	int output;

	max_signal = 0;
	input = get_valid(input);
	while (input > 0)
	{
		sequence = ft_itoa(input);
		output = phase_iterator(orig, sequence);
		if (output > max_signal)
			max_signal = output;
		printf("SEQUENCE: %s | signal generated: %d\n", sequence, output);
		input = get_valid(input - 1);
	}
	return (max_signal);
}

int		main(int argc, char **input)
{
	int fd;
	long *org;
	long max_signal;

	if (argc < 2)
		return (0);
	fd = open(input[1], O_RDONLY);
	org = get_array(fd, 2000);
//	print_array(org, 100);
//	max_signal = input_iterator(99999, org);
	max_signal = intcode(org, 0, '1');
//	print_array(org, 100);
	printf("BOOST: %ld\n", max_signal);
	return (0);
}
