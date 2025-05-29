/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:03:03 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/29 11:17:44 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	show_cmds(t_data *data)
{
	(void)data;
}

int	key_update_direction(int key, t_player *p, t_map *map)
{
	if (key == 'a')
	{
		printf("DIR s\n");
		p->pa += 0.2;
		p->dx = cos(p->pa) * STEP;
		p->dy = sin(p->pa) * STEP;
		printf("dir : {%lf, %lf}\n", p->dx, p->dy);
	}
	if (key == 'd')
	{
		printf("DIR RIGHT\n");
		p->pa -= 0.2;
		p->dx = cos(p->pa) * STEP;
		p->dy = sin(p->pa) * STEP;
		printf("dir : {%lf, %lf}\n", p->dx, p->dy);
	}
	return (0);
	(void)map;
}

# define SECURE_STEP 10
static int wall_hit(int mapXidx, int mapYidx, t_ray *ray, t_map *map)
{
	mapXidx = ray->rx / map->mapS;
	mapYidx = ray->ry / map->mapS;
	if (mapXidx >= 0 && mapXidx < map->max.x * SCALE_MAP && mapYidx >= 0 && mapYidx < map->max.y * SCALE_MAP)
		if (map->imap[mapYidx][mapXidx] == 1)// || map->imap[mapYidx][mapXidx] == -PLAYER_POS)
			return (1);
	return (0);
}
int	key_update_position(int key, t_data *data, t_player *p)
{
	if (data->menu.is_menu)
		return (1);
	
	if (key == A_UP && p->py < HI - SECURE_STEP)
	{
		p->py += p->dx;
		p->px += p->dy;
	}
	else if (key == A_LEFT && p->px > SECURE_STEP)
	{
		p->px += p->dx;
		p->py -= p->dy;
	}
	else if (key == A_RIGHT && p->px < WI - SECURE_STEP)
	{
		p->px -= p->dx;
		p->py += p->dy;
	}
	else if (key == A_DOWN && p->py > SECURE_STEP) 
	{
		p->py -= p->dx;
		p->px -= p->dy;
	}
	key_update_direction(key, p, &data->run.map);
	return (0);
}

static void	define_action(t_data *data)
{
	if (data->menu.option == 1)
		data->menu.is_menu = 0;
	if (data->menu.option == 2)
		show_cmds(data);
	if (data->menu.option == 3)
		close_window(data);
}

static int	key_menu(int key, t_data *data)
{
	if (key == 'q')
		data->menu.is_menu = 0;
	if (key == A_DOWN && data->menu.option < MENU_SLOTS)
		data->menu.option++;
	if (key == A_UP && data->menu.option > 1)
		data->menu.option--;
	if (key == ENTER || key == 'o')
		define_action(data);
	return (0);
}
// constants
//#define TWO_PI 6.2831853
//#define RAY_COUNT 720
//#define RAY_STEP 1.0
//
//static void adjust_ray_data(t_ray *ray, t_data *data)
//{
//	ray->rx = data->run.player.px;
//	ray->ry = data->run.player.py;
//	ray->dx = cosf(ray->ra) * RAY_STEP;
//	ray->dy = sinf(ray->ra) * RAY_STEP;
//}
//
//static void update_ray_pos(t_ray *ray, t_map *map)
//{
//	ray->rx += ray->dx;
//	ray->ry += ray->dy;
//	ray->mapXidx = (int)(ray->rx / map->mapS);
//	ray->mapYidx = (int)(ray->ry / map->mapS);
//}
//
static void draw_line_(int x0, int y0, int x1, int y1, t_data *data)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		my_mlx_pixel_put(data, x0, y0, BLUE);
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

//void check_player_direction(t_data *data, t_player *player)
//{
//	t_ray ray;
//	float ra;
//	int i;
//
//	for (i = 0; i < RAY_COUNT; i++)
//	{
//		ra = ((float)i / (float)RAY_COUNT) * TWO_PI;
//		ray.ra = ra;
//		adjust_ray_data(&ray, data);
//		ray.depth = 0;
//
//		while (ray.depth++ < 100)
//		{
//			update_ray_pos(&ray, &data->run.map);
//			if (wall_hit(data, ray.rx, ray.ry))
//				break;
//		}
//
//		draw_line_(
//			(int)(data->run.player.px),
//			(int)(data->run.player.py),
//			(int)ray.rx,
//			(int)ray.ry,
//			data
//		);
//	}
//	(void)player;
//}
static void	adjust_ray_data(t_ray *ray, t_data *data)
{
//	if (ray->ra > 2 * PI)
//		ray->ra -= 2 * PI;
	ray->rx = data->run.player.px;
	ray->ry = data->run.player.py;
	ray->dx = cos(ray->ra) * 1;
	ray->dy = sin(ray->ra) * 1;
}

static void	update_ray_pos(t_ray *ray, t_map *map)
{
	ray->rx += ray->dy;
	ray->ry += ray->dx;
	ray->mapXidx = (int)((ray->rx) / map->mapS);
	ray->mapYidx = (int)((ray->ry) / map->mapS);
}

void	check_player_direction(t_data *data)
{
	t_ray	ray;
	int		r;
	float	step = 6.28 / 360;
	float	ra = 0;

	r = NUM_RAYS;
	while (r-- > 0)
	{
		ray.ra = ra;
		adjust_ray_data(&ray, data);
		ray.depth = 0;
		while (ray.depth++ < 30)
		{
			update_ray_pos(&ray, &data->run.map);
			if (wall_hit(ray.mapXidx, ray.mapYidx, &ray, &data->run.map))
				break ;
		}
		draw_line_(data->run.player.px + PSIZE / 2,
		          data->run.player.py + PSIZE / 2,
		          (int)ray.rx, (int)ray.ry, data);
		ra += step;
	}
}

int	key_update_env(int key, t_data *data)
{
	t_player	player;

	player = data->run.player;
	if (key == ESC)
		close_window(data);
	if (key == 'h')
		show_cmds(data);
	if (key == 'm')
		data->menu.is_menu = 1;
	check_player_direction(data);
	key_update_position(key, data, &player);
	data->run.player = player;
	if (data->menu.is_menu)
		return (key_menu(key, data));
	return (0);
}

