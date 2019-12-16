/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_hullpaintbot.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/14 12:39:42 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/14 12:39:42 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day11.h"

t_coord		ft_turn(int dir, t_coord old, int steps)
{
	t_coord new;
	char c;

//	printf("old coord\nx%d, y%d | dir %d | steps %d\n", old.x, old.y, dir, steps);
	new = old;
	if (steps % 2 == 0)
		c = 'y';
	else
		c = 'x';
	if (dir)
	{
		if (c == 'y')
			new.y += 1;
		if (c == 'x')
			new.x += 1;
	}
	else
	{
		if (c == 'y')
			new.y -= 1;
		if (c == 'x')
			new.x -= 1;	
	}
//	printf("adjusted coord\nx%d, y%d | coord adjusted: %c\n", new.x, new.y, c);
	return (new);
}

int			ft_hull_painter(long *input)
{
	t_tile	*lst;
	t_tile	*new;
	t_coord	coords;
	t_inst	instruction;
	long	out;
	int		in;
	int		steps;

	out = 0;
	steps = 1;
	coords = reset_coord();
	lst = NULL;
	while (1) //inf loop
	{
		new = ft_tile_find(&lst, coords);			//try to find the tile
		if (new == NULL)
		{
			new = ft_tile_new(coords, 0);			//if it doesnt exist we make it, initializing at color 0
			ft_tile_addbck(&lst, new);
		}
		in = new->color;
		out = ft_intcode(input, in, '0');			//to get the color we need to paint it to, we run the intcode
		if (out == -1)
			break ;
//		instruction = get_inst(out);
//		new->color = instruction.color;
		new->color = out;							//we change the color of the current tile
		out = ft_intcode(input, in, '0');	//we run the intcode with the old color to get the direction
		if (out == -1)
			break ;
		coords = ft_turn(out, coords, steps);		//we change the coordinates based on the direction
		steps++;
	}
//	ft_makefield(&lst);
	ft_print_tile(lst);
	printf("tiles painted: %d\n", ft_tile_count(&lst));
}
