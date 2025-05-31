/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_computing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:51:46 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 13:27:22 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	wall_hit(int mapXidx, int mapYidx, t_ray *ray, t_map *map)
{
	mapXidx = ray->rx / map->map_s;
	mapYidx = ray->ry / map->map_s;
	if (mapXidx >= 0 && mapXidx < map->max.x * SCALE_MAP
		&& mapYidx >= 0 && mapYidx < map->max.y * SCALE_MAP)
		if (map->imap[mapYidx][mapXidx] == 1)
			return (1);
	return (0);
}

void	adjust_ray_data(t_ray *ray, t_data *data)
{
	if (ray->ra > 2 * PI)
		ray->ra -= 2 * PI;
	ray->rx = data->run.player.px;
	ray->ry = data->run.player.py;
	ray->dx = cos(ray->ra) * 1;
	ray->dy = sin(ray->ra) * 1;
}

void	update_ray_pos(t_ray *ray, t_map *map)
{
	ray->rx += ray->dy;
	ray->ry += ray->dx;
	ray->mapx_idx = (int)((ray->rx) / map->map_s);
	ray->mapy_idx = (int)((ray->ry) / map->map_s);
}

t_texture	*select_texture(t_data *data, t_ray *ray)
{
	if (fabs(ray->dx) > fabs(ray->dy))
	{
		if (ray->dx > 0)
			return (&data->textures[WEST]);
		else
			return (&data->textures[EAST]);
	}
	else
	{
		if (ray->dy > 0)
			return (&data->textures[NORTH]);
		else
			return (&data->textures[SOUTH]);
	}
}
