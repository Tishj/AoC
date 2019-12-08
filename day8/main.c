/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/08 08:56:16 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/08 08:56:16 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day8.h"

void	fill_image(char *image, int size, char c)
{
	int i;

	i = 0;
	while (i < size)
	{
		image[i] = c;
		i++;
	}
	image[i] = 0;
}

char	*convert_layers(char **layers)
{
	char *image;
	int l;
	int i;

	image = malloc(sizeof(char) * (150 + 1));
	fill_image(image, 150, '2');
	l = 0;
	while (layers[l])
	{
		i = 0;
		while (layers[l][i])
		{
			if (image[i] == '2')
				image[i] = layers[l][i];
			i++;
		}
		l++;
	}
	return (image);
}

int	print_layers(char **str)
{
	int i;
	int j;
	int n;
	int zl;
	int zmin;
	int o;
	int t;

	i = 0;
	zmin = 0;
	while (str[i])
	{
		j = 0;
		n = 0;
		o = 0;
		t = 0;
		while (str[i][j])
		{
			if (str[i][j] == '0')
				n++;
			if (str[i][j] == '1')
				o++;
			if (str[i][j] == '2')
				t++;
			if (j % 25 == 0)
				write(1, "\n", 1);
			write(1, &str[i][j], 1);
			j++;
		}
		printf("\n\nLayer %d | %d 0 characters\n", i, n);
		printf("Layer %d | 1(%d) * 2(%d) = res(%d)\n\n", i, o, t, o * t);
		if (zmin > n || zmin == 0)
		{
			zmin = n;
			zl = i;
		}
		i++;
	}
	printf("Min zero: %d | on layer %d\n", zmin, zl);
	return (n);
}

char	**get_layers(int fd, int l, int r, int c)
{
	char **layers;
	int red;
	int i;

	i = 0;
	layers = (char **)malloc(sizeof(char *) * (l + 1));
	while (i <= l)
	{
		layers[i] = (char *)malloc(sizeof(char) * ((r * c) + 1));
		red = read(fd, &layers[i][0], 150);
		layers[i][150] = 0;
		i++;
	}
	layers[i] = 0;
	return (layers);
}

void	print_image(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (i % 25 == 0)
			printf("\n");
		if (str[i] == '1')
		{
			printf("\033[1;29m");
			printf("X");
			printf("\033[0m");
		}
		if (str[i] == '0')
		{
			printf("\033[0;30m");
			printf("X");
			printf("\033[0m");
		}
		i++;
	}
}

int		main(int argc, char **input)
{
	int fd;
	char **l;
	char *image;
	int red;
	int layer;

	if (argc < 2)
		return (0);
	fd = open(input[1], O_RDONLY);
	l = get_layers(fd, 99, 25, 6);
//	print_layers(l);
	image = convert_layers(l);
	print_image(image);
	return (0);
}
