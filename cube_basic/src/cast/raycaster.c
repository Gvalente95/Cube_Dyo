/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 06:04:42 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/28 06:04:20 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include "cub.h"

int	mapX=15, mapY=8, mapS=64;
//int	map[8][15]=
//	{
//		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//		{1,0,1,0,0,1,0,0,0,0,0,0,0,0,1},
//		{1,0,1,0,0,1,0,0,0,0,0,0,0,0,1},
//		{1,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
//		{1,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
//		{1,0,0,0,0,1,0,0,0,0,0,1,0,0,1},
//		{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
//		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
//	};

#define FOV_ANGLE 60.0
#define TILE_SIZE 16
#define FOV 1.0471975512 // 60 degrés en radians
#define NUM_RAYS WI

void	draw_line(int x0, int y0, int x1, int y1, t_data *data)
{
	int	dx = abs(x1 - x0);
	int	dy = abs(y1 - y0);
	int	sx = x0 < x1 ? 1 : -1;
	int	sy = y0 < y1 ? 1 : -1;
	int	err = dx - dy;	
	
	while (1)
	{
		my_mlx_pixel_put(data, x0, y0, GREEN);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	draw_2Dwall(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = x + 1;
	while (i < x + data->run.map.mapS - 1)
	{
		j = y + 1;
		while (j < y + data->run.map.mapS - 1)
			my_mlx_pixel_put(data, i, j++, color);
		i++;
	}
}

void	draw_2Dmap(t_data *data)
{
	int	x;
	int	y;
	int	x0;
	int	y0;
	int	color;

	y = 0;
	while (y < data->run.map.max.y * SCALE_MAP)
	{
		x = 0;
		while (x < data->run.map.max.x * SCALE_MAP)
		{
			if (data->run.map.imap[y][x] == 1)
				color = WHITE;
			else if (data->run.map.imap[y][x] == 2)
				color = BLUE;
			else
				color = RED;
			x0 = x * data->run.map.mapS;
			y0 = y * data->run.map.mapS;
			draw_2Dwall(data, x0, y0, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data)
{
	int	x;
	int	y;

	if (data->run.player.px == 0)
	{
		data->run.player.px = 300;
		data->run.player.py = 300;
	}
	x = data->run.player.px;
	while (x <= data->run.player.px + PSIZE)
	{
		y = data->run.player.py;
		while (y <= data->run.player.py + PSIZE)
			my_mlx_pixel_put(data, x, y++, BLUE);
		x++;
	}
}

int	wall_hit(int mapXidx, int mapYidx, t_ray *ray, t_map *map)
{
	if (mapXidx >= 0 && mapXidx < map->max.x && mapYidx >= 0 && mapYidx < map->max.y)
		return (map->imap[mapYidx][mapXidx]);
	return (false);
	(void)ray;
}

int	extract_length(t_data *data, int x, int  y)
{
	float	dx;
	float	dy;

	dx = x - data->run.player.px;
	dy = y - data->run.player.py;
	return (sqrt(dx * dx + dy * dy));
}

void	draw_vertical_line(t_data *data, int start, int end, int ray, int distance, int color)
{
	int		shade;
	int		shaded_color;

	if (color == WHITE)
	{
		shade = 255 - (distance * 255 / NUM_RAYS);
		if (shade < 0)
			shade = 0;
		if (shade > 255)
			shade = 255;
	}
	else
		shaded_color = color;
	while (start < end)
	{
		if (start >= 0 && start < HI)
		{
			if (color == WHITE)
				shaded_color = (shade << 16) | (shade << 8) | shade;
			my_mlx_pixel_put2(data, ray, start, shaded_color);
		}
		start++;
	}
}

#define PROJECTION_CONSTANT WI * 30

void cast_length(t_data *data, float distance, int ray)
{
    float	wall_height;
    int		start_y;
    int		end_y;

	wall_height = PROJECTION_CONSTANT / distance;
	start_y = HI / 2 - wall_height / 2;
	end_y = HI / 2 + wall_height / 2;
	if (start_y < 0)
		start_y = 0;
	if (end_y > HI)
	    end_y = HI;
	draw_vertical_line(data, 0, start_y, ray, distance, BLUE);
	draw_vertical_line(data, start_y, end_y, ray, distance, WHITE);
	draw_vertical_line(data, end_y, HI, ray, distance, GREEN);
}

void	adjust_ray_data(t_ray *ray, t_data *data)
{
	if (ray->ra > 2 * PI)
		ray->ra -= 2 * PI;
	ray->rx = data->run.player.px;
	ray->ry = data->run.player.py;
	ray->dx = -cos(ray->ra) * 1;
	ray->dy = sin(ray->ra) * 1;
}

void	update_ray_pos(t_ray *ray, t_map *map)
{
	ray->ry += ray->dy;
	ray->mapXidx = (int)((ray->rx) / map->mapS);
	ray->mapYidx = (int) ((ray->ry) / map->mapS);
	ray->fx_idx = ray->rx / map->mapS;
	ray->fy_idx = ray->ry / map->mapS;
}

void	cast_rays(t_data *data)
{
	t_ray	ray;
	int		r;	
	float	distance;

	ray.step = FOV / NUM_RAYS;
	ray.ra = (data->run.player.pa - PI / 2 - (FOV / 2));
	if (ray.ra < 0)
		ray.ra += 2 * PI;
	r = NUM_RAYS;
	while (r > 0)
	{
		ray.depth = 0;
		adjust_ray_data(&ray, data);
		while (ray.depth++ < 1000)
		{
			update_ray_pos(&ray, &data->run.map);
			if (wall_hit(ray.mapXidx, ray.mapYidx, &ray, &data->run.map))
				break ;
		}
		distance = extract_length(data, ray.rx, ray.ry);
		cast_length(data, distance, r--);
		draw_line(data->run.player.px + PSIZE / 2,
			data->run.player.py + PSIZE / 2, (int)ray.rx, (int)ray.ry, data);
		ray.ra += ray.step;
	}
}

void	compute_raycast(t_data *data)
{
	draw_2Dmap(data);
	draw_player(data);
	cast_rays(data);
}
