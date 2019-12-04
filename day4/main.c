/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 22:06:35 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/04 22:06:35 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day4.h"

char	*get_array(int fd)
{
	int red;
	char string[99];
	char c;
	int i;

	i = 0;
	red = read(fd, &c, 1);
	while (red > 0 && c != '-')
	{
		string[i] = c;
		i++;
		red = read(fd, &c, 1);
	}
	return (strdup(string));
}

int		match_counter(char *start)
{
	int res;
	char c;
	int i;
	int tmp;

	c = '0';
	res = 6;
	while (c >= '0' && c <= '9')
	{
		i = 0;
		tmp = 0;
		while (start[i])
		{
			if (start[i] == c)
				tmp++;
			i++;
		}
		if (tmp >= 2 && tmp <= res)
			res = tmp;
		c++;
	}
	return (res);
}

int		is_possible(char *start)
{
	int dub;
	int no_dec;
	int i;
	char temp;

	i = 0;
	dub = 0;
	no_dec = 1;
	while (start[i])
	{
		if (start[i + 1])
		{
			if (start[i] == start[i + 1])
				dub = 1;
			if (start[i] > start[i + 1])
				no_dec = 0;
		}
		i++;
	}
	if (dub == 1)
		if (match_counter(start) > 2)
			dub = 0;
	if (dub == 1 && no_dec == 1)
		return (1);
	return (0);
}

int		counter(int start, int end)
{
	int res;
	char *tmp;

	res = 0;
	while (start <= end)
	{
		tmp = ft_itoa(start);
		res += is_possible(tmp);
		start++;
	}
	return (res);
}

int		main(int argc, char **input)
{
	int fd;
	int	start;
	int	end;

	if (argc > 1)
		fd = open(input[1], O_RDONLY);
	start = atoi(get_array(fd));
	end = atoi(get_array(fd));
	printf("start: %d | end: %d\n", start, end);
	printf("possible combinations: %d\n", counter(start, end));
	return (0);
}
