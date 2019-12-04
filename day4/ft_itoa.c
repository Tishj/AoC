/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:18:28 by tbruinem       #+#    #+#                */
/*   Updated: 2019/11/19 11:43:31 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day4.h"

static	int		get_length(int nb)
{
	int				i;
	unsigned int	n;

	i = 0;
	if (nb <= 0)
	{
		n = nb * -1;
		i++;
	}
	else
		n = nb;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

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

	length = get_length(n);
	str = malloc(length + 1);
	if (str == NULL)
		return (NULL);
	assign_digit(str, n, length - 1);
	str[length] = 0;
	return (str);
}
