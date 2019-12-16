/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_do_op.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 16:30:41 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/13 16:30:41 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"

void	ft_do_add(long *array, int *index, int *code, int *rbase)
{
	long p1;
	long p2;
	int pos;
	int posmode;

	p1 = ft_get_value(code, array, (*index) + 1, rbase);
	p2 = ft_get_value(code, array, (*index) + 2, rbase);
	posmode = ft_mod(code);
	if (posmode == 0)
		pos = array[*index + 3];
	if (posmode == 1)
		pos = *index + 3;
	if (posmode == 2)
		pos = array[*index + 3] + *rbase;
	array[pos] = p1 + p2;
	ft_debug('+', *index, array, p1, p2);
	*index = (*index) + 4;
}

void	ft_do_mul(long *array, int *index, int *code, int *rbase)
{
	long p1;
	long p2;
	int pos;
	int posmode;

	p1 = ft_get_value(code, array, (*index) + 1, rbase);
	p2 = ft_get_value(code, array, (*index) + 2, rbase);
	posmode = ft_mod(code);
	if (posmode == 0)
		pos = array[*index + 3];
	if (posmode == 1)
		pos = *index + 3;
	if (posmode == 2)
		pos = array[*index + 3] + *rbase;
	array[pos] = p1 * p2;
	ft_debug('*', *index, array, p1, p2);
	*index = (*index) + 4;
}

void	ft_do_set(long *array, int *index, int *code, char setting,
		int *start, long output, int *rbase)
{
	long p1;
	int pos;
	int posmode;

	p1 = ft_get_value(code, array, (*index) + 1, rbase);
	posmode = ft_mod(code);
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
	ft_debug('i', *index, array, p1, 0);
	*index = (*index) + 2;
}

long	ft_do_prnt(long *array, int *index, long *out, int *code, int *rbase)
{
	long p1;

	p1 = ft_get_value(code, array, (*index) + 1, rbase);
//	printf("output signal: %ld\n", p1);
	*index = (*index) + 2;
	ft_debug('o', *index, array, p1, 0);
	*out = p1;
	return (1);
}

void	ft_do_jump(long *array, int *index, int *code, int op, int *rbase)
{
	long p1;
	long p2;
//	int pos;
//	int posmode;

	p1 = ft_get_value(code, array, (*index) + 1, rbase);
	p2 = ft_get_value(code, array, (*index) + 2, rbase);
/* 	if (posmode == 0)
		pos = array[*index + 3];
	if (posmode == 1)
		pos = *index + 3;
	if (posmode == 2) */
	if (p1 != 0 && op == 5)
	{
		(*index) = p2;
		ft_debug('t', *index, array, p1, p2);
	}
	else if (p1 == 0 && op == 6)
	{
		(*index) = p2;
		ft_debug('f', *index, array, p1, p2);
	}
	else
		(*index) = (*index) + 3;
}

void	ft_do_comp(long *array, int *index, int *code, int op, int *rbase)
{
	long p1;
	long p2;
	int pos;
	int posmode;

	p1 = ft_get_value(code, array, (*index) + 1, rbase);
	p2 = ft_get_value(code, array, (*index) + 2, rbase);
	posmode = ft_mod(code);
	if (posmode == 0)
		pos = array[*index + 3];
	if (posmode == 1)
		pos = *index + 3;
	if (posmode == 2)
		pos = array[*index + 3] + *rbase;
	if (p1 < p2 && op == 7)
	{
		array[pos] = 1;
		ft_debug('<', *index, array, p1, p2);
	}
	else if (p1 == p2 && op == 8)
	{
		array[pos] = 1;
		ft_debug('=', *index, array, p1, p2);
	}
	else
		array[pos] = 0;
	*index = (*index) + 4;
}

void	ft_do_rbase(long *array, int *index, int *code, int op, int *rbase)
{
	long p1;

	p1 = ft_get_value(code, array, (*index) + 1, rbase);
//	printf("index: %d | rbase: %d | to add: %ld | from index: %d\n", *index, *rbase, p1, *index + *rbase);
	*rbase = *rbase + p1;
	ft_debug('r', *index, array, p1, *rbase);
	*index = (*index) + 2;
}

long	ft_do_op(long *array, int *i, long *output, int *start, char setting, int *rbase)
{
	int op;
	int code;

	code = array[*i];
	op = ft_mod(&code);
	if (ft_mod(&code) != 0 || (op < 1 || 9 < op))
	{
		*i = *i + 1;
		return (0);
	}
//	printf("code :%d | op: %d\n", code, op);
	if (op == 1)
		(ft_do_add(array, i, &code, rbase));
	if (op == 2)
		(ft_do_mul(array, i, &code, rbase));
	if (op == 3)
		(ft_do_set(array, i, &code, setting, start, *output, rbase));
	if (op == 4)
		return (ft_do_prnt(array, i, output, &code, rbase));
	if (op == 5)
		(ft_do_jump(array, i, &code, op, rbase));
	if (op == 6)
		(ft_do_jump(array, i, &code, op, rbase));
	if (op == 7)
		(ft_do_comp(array, i, &code, op, rbase));
	if (op == 8)
		(ft_do_comp(array, i, &code, op, rbase));
	if (op == 9)
		(ft_do_rbase(array, i, &code, op, rbase));
//	printf("I stopped working\n");
	return (0);
}
