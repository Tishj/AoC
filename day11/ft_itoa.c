/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/07 12:37:36 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/07 12:37:36 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"

static	void	assign_digit(char *str, int n, int i)
{
	unsigned int nb;

	if (n < 0)
	{
		str[0] = '-';
		nb = n * -1;
	}
	else
		nb = n;
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[i] = (nb % 10) + '0';
		i--;
		nb = nb / 10;
	}
}

char			*ft_itoa(int n)
{
	char	*str;
	int		length;
	int i;

	i = 0;
	str = malloc(5 + 1);
	if (str == NULL)
		return (NULL);
	while (i < 5)
	{
		str[i] = '0';
		i++;
	}
	assign_digit(str, n, 5 - 1);
	str[5] = 0;
	return (str);
}
