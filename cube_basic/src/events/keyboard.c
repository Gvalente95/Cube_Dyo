/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:03:03 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/29 05:39:42 by dyodlm           ###   ########.fr       */
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

int	wall_hit(t_data *data, float dx, float dy)
{
	int	mapXidx;
	int	mapYidx;

	mapXidx = dx / data->run.map.mapS;
	mapYidx = dy / data->run.map.mapS;
	if (mapXidx >= 0 
		&& mapXidx < data->run.map.max.x * SCALE_MAP
			&& mapYidx >= 0 && mapYidx < data->run.map.max.y * SCALE_MAP)
		return (1);
	return (0);
}

int	key_update_position(int key, t_data *data, t_player *p)
{
	if (data->menu.is_menu)
		return (1);
	
	if (key == A_UP && p->py < HI - SECURE_STEP)
//		&& !would_wall_hit(data, p->dx + p->dx, p->py + p->dy))
	{
		p->py += p->dx;
		p->px += p->dy;
	}
	else if (key == A_LEFT && p->px > SECURE_STEP)
//		&& !would_wall_hit(data, p->dx + p->dx, p->py - p->dy))
	{
		p->px += p->dx;
		p->py -= p->dy;
	}
	else if (key == A_RIGHT && p->px < WI - SECURE_STEP)
//		&& !would_wall_hit(data, p->dx - p->dx, p->py + p->dy))
	{
		p->px -= p->dx;
		p->py += p->dy;
	}
	else if (key == A_DOWN && p->py > SECURE_STEP) 
//		&& !would_wall_hit(data, p->dx - p->dx, p->py - p->dy))
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

static int	extract_length(t_data *data, int x, int  y)
{
	float	dx;
	float	dy;

	dx = x - data->run.player.px;
	dy = y - data->run.player.py;
	return (sqrt(dx * dx + dy * dy));
}

static void	adjust_ray_data(t_ray *ray, t_data *data)
{
	ray->rx = data->run.player.px;
	ray->ry = data->run.player.py;
	ray->dx = -cos(ray->ra) * 3;
	ray->dy = sin(ray->ra) * 3;
}

static void	update_ray_pos(t_ray *ray, t_map *map)
{
	ray->rx += ray->dx;
	ray->ry += ray->dy;
	ray->mapXidx = (int)((ray->rx) / map->mapS);
	ray->mapYidx = (int)((ray->ry) / map->mapS);
}

void	check_player_direction(t_data *data, t_player *player)
{
	t_ray	ray;
	int		r;
	float	distance;
	float	step = FOV / NUM_RAYS;
	float	ra = data->run.player.pa - (FOV / 2);

	r = NUM_RAYS;
	while (r > 0)
	{
		ray.ra = ra;
		adjust_ray_data(&ray, data);
		ray.depth = 0;
		while (ray.depth++ < 50)
		{
			update_ray_pos(&ray, &data->run.map);
			if (wall_hit(data, ray.rx, ray.ry))
				break ;
		}
		distance = extract_length(data, ray.rx, ray.ry);
		draw_line(data->run.player.px + PSIZE / 2,
		          data->run.player.py + PSIZE / 2,
		          (int)ray.rx, (int)ray.ry, data);
		ra += step;
		r--;
	}
	(void)distance;
	(void)player;
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
//	check_player_direction(data, &player);
	key_update_position(key, data, &player);
	data->run.player = player;
	if (data->menu.is_menu)
		return (key_menu(key, data));
	return (0);
}

