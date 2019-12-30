/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_asteroid.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tbruinem <tbruinem@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/29 12:40:02 by tbruinem       #+#    #+#                */
/*   Updated: 2019/12/29 12:40:02 by tbruinem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "day10.h"

int		ft_asteroid_count(char **map)
{
	int ast;
	int x;
	int y;

	y = 0;
	ast = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '#')
				ast++;
			x++;
		}
		y++;
	}
	return (ast);
}

void	ft_asteroid_vaporizer(char **map, int max_size)
{
	t_ray		ray;
	t_fcoord	direction;
	t_list		*deleted;
	t_coord		pivot;
	int			ast;
	int			dir;

	pivot = ft_coord_init(max_size / 2, max_size / 2);		//initialize the pivot
	deleted = NULL;
	direction = ft_fcoord_init(0.0, -1.0);					//start the direction at Q_TOPRIGHT
	ast = ft_asteroid_count(map);							//count the remaining asteroids
	dir = Q_TOPRIGHT;
	while (ast > 0)											//loop while there are still asteroids remaining
	{
		ray = ft_ray_init(pivot, direction);				//initialize the ray | pivot, step and total steps;
		ft_asteroid_del(map, ray, pivot, max_size);			//run asteroid delete using the ray we fired.
		dir = ft_direction_get(direction, dir);				//check if the direction needs to be updated.
		direction = ft_direction_translate(dir, direction);	//increase the direction X and Y based on the dir.
		printf("\e[1;1H\e[2J");
		print_array(map);									//print the array
//		usleep(10000);
		ast = ft_asteroid_count(map);						//recount asteroids.
	}
}

/* void	ft_asteroid_find(char **map, t_coord start, int max_size)
{
	t_coord step;
	t_stepper data;

	data.start = start;
	data.total.x = 0;
	data.total.y = 0;
	step.y = -max_size;
	while (step.y < max_size)
	{
		step.x = -max_size;
		while (step.x < max_size)
		{
			if (step.x != 0 || step.y != 0)
			{
				data.step.x = step.x;
				data.step.y = step.y;
				ft_asteroid_scout(map, data, max_size);
			}
			step.x++;
		}
		step.y++;
	}
} */

/* void	ft_asteroid_scout(char **map, t_stepper data, int max_size)
{
	t_coord current;

	current.y = (data.start.y + data.total.y) + data.step.y;
	current.x = (data.start.x + data.total.x) + data.step.x;
	if (is_it_safe(map, current, max_size) == 0)
		return ;
	data.total.x += data.step.x;
	data.total.y += data.step.y;
	if (map[current.y][current.x] == '#')
	{
		data.total = set_course(data, max_size);
		if (data.total.x == 0 && data.total.y == 0)
			return ;
		return (ft_asteroid_del(map, data.total, current, max_size));
	}
	return (ft_asteroid_scout(map, data, max_size));
} */

void	ft_asteroid_del(char **map, t_ray ray, t_coord old, int max_size)
{
	t_coord current;
	t_fcoord total;

//	if (ray.stp.x >= 0)
		ray.ttl.x += ray.stp.x;
//	else
//		ray.ttl.x -= ray.stp.x;
//	if (ray.stp.y >= 0)
		ray.ttl.y += ray.stp.y;
//	else
//		ray.ttl.y -= ray.stp.y;
	current.y = (old.y + (int)ray.ttl.y);
	current.x = (old.x + (int)ray.ttl.x);
	printf("direction: X%f | Y%f\n", ray.stp.x, ray.stp.y);
	if (is_it_safe(map, current, max_size) == 0)
		return ;
	if (map[current.y][current.x] == '#')
	{
		map[current.y][current.x] = 'R';
		return ;
	}
	if (map[current.y][current.x] == '.')
		map[current.y][current.x] = 'D';
	return (ft_asteroid_del(map, ray, current, max_size));
}
