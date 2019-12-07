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
//		printf("current: %c\n", c);
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
//	debug_me('+', (*index), array, p1, p2);
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
//	debug_me('*', (*index), array, p1, p2);
	*index = (*index) + 4;
}

int		do_set(int *array, int *index, int *code, int INPUTS, int phase, int *start)
{
	int p1;
	int pos;
	char *str;

	str = ft_itoa(INPUTS);
//	printf("INPUTS: %s", str);
	pos = array[(*index) + 1];
	if (*start == 1)
	{
		p1 = str[phase] - '0';
		*start = 0;
	}
	else
		p1 = 0;
//	printf("INPUTS: %s | AMP:%5d | current input: %d\n", str, *len, p1);
	array[pos] = p1;
//	debug_me('=', (*index), array, p1, 0);
	*index = (*index) + 2;
}

int		do_prnt(int *array, int *index, int *code, int *t_thrust)
{
	int p1;
	int pos;

	pos = array[(*index) + 1];
	p1 = get_value(code, array, (*index) + 1);
	*t_thrust += p1;
//	printf("THRUSTER SIGNAL: %d\n", p1);
//	printf("%-6d | %d,%d                     |\n\nPRINT: %d\n\n", (*index), array[(*index)], array[(*index)], p1);
	*index = (*index) + 2;
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
//	debug_me('*', (*index), array, p1, p2);
	*index = (*index) + 4;
}

void	do_op(int *array, int *index, int code, int *t_thrust, int INPUTS, int phase, int *start)
{
	int op;

	op = get_mod(&code);
	if (get_mod(&code) != 0)
	{
		*index = *index + 1;
		return ;
	}
	if (op == 1)
		(do_add(array, index, &code));
	else if (op == 2)
		(do_mul(array, index, &code));
	else if (op == 3)
		(do_set(array, index, &code, INPUTS, phase, start));
	else if (op == 4)
		(do_prnt(array, index, &code, t_thrust));
	else if (op == 5)
		(do_jump(array, index, &code, op));
	else if (op == 6)
		(do_jump(array, index, &code, op));
	else if (op == 7)
		(do_comp(array, index, &code, op));
	else if (op == 8)
		(do_comp(array, index, &code, op));
	else
		*index = *index + 1;
}

void	clean_array(char *array)
{
	int i;

	i = 0;
	while (array[i])
	{
		array[i] = 0;
		i++;
	}
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

int		main(int argc, char **input)
{
	int fd;
	int i;
	int *array;
	char s_signal[5];
	int phase = 0;
	int in;
	int INPUTS;
	int t_thrust = 0;
	int t_signal = 0;
	int m_signal = 0;
	int len = 0;
	int start = 1;
	int *org;

	INPUTS = 99999;
	if (argc < 2)
		return (0);
	fd = open(input[1], O_RDONLY);
	org = get_array(fd, 506);
	array = array_dup(org, 506);
//	print_array(array, 506);
//	return (0);
	INPUTS = get_valid(INPUTS - 1);
	while (INPUTS > 0)
	{
		printf("INPUTS: %d\n", INPUTS);
		while (phase < 5)
		{
			i = 0;
//			printf("PHASE: %d\n", phase);
			while (array[i] != 99)
			{
//				printf("index: %d\n", i);
				in = (array[i]);
				do_op(array, &i, in, &t_thrust, INPUTS, phase, &start);
			}
			start = 1;
			s_signal[phase] = (t_thrust % 10) + '0';
			t_thrust = 0;
			phase++;
			free(array);
			array = array_dup(org, 506);
		}
		printf("SIGNAL: %s\n\n", s_signal);
		phase = 0;
		t_signal = atoi(s_signal);
		if (t_signal > m_signal)
			m_signal = t_signal;
		clean_array(s_signal);
//		break ;
		INPUTS = get_valid(INPUTS - 1);
	}
	printf("max signal: %d\n", m_signal);
	return (0);
}
