/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_checkers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:59:22 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 12:49:07 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	help(t_data *data, t_ray *ray, int ra, int distance)
{
	if (ra == 200)
	{
		if (distance < MOVE_LIMIT + 10)
			data->run.player.dir.down = 0;
		else
			data->run.player.dir.down = 1;
	}
	else if (ra == 290)
	{
		if (distance < MOVE_LIMIT + 10)
			data->run.player.dir.left = 0;
		else
			data->run.player.dir.left = 1;
	}
	(void)ray;
}

void	load_length(t_data *data, t_ray *ray, int ra)
{
	float		distance;

	distance = extract_length(data, (int)ray->rx, (int)ray->ry);
	if (ra == 0)
	{
		if (distance < MOVE_LIMIT + 10)
			data->run.player.dir.up = 0;
		else
			data->run.player.dir.up = 1;
	}
	else if (ra == 90)
	{
		if (distance < MOVE_LIMIT + 10)
			data->run.player.dir.right = 0;
		else
			data->run.player.dir.right = 1;
	}
	else
		help(data, ray, ra, distance);
}

void	check_player_direction(t_data *data)
{
	t_ray	ray;
	int		r;
	float	step;
	float	ra;

	step = (PI * 2) / 360;
	ra = data->run.player.pa;
	r = 360;
	while (r-- > 0)
	{
		ray.ra = ra;
		adjust_ray_data(&ray, data);
		ray.depth = 0;
		while (ray.depth++ < MOVE_LIMIT + 20)
		{
			update_ray_pos(&ray, &data->run.map);
			if (wall_hit(ray.mapx_idx, ray.mapy_idx, &ray, &data->run.map))
				break ;
		}
		load_length(data, &ray, r);
		ra += step;
	}
}
