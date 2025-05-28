/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:03:03 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/28 07:40:28 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	show_cmds(t_data *data)
{
	(void)data;
}

int	key_update_direction(int key, t_player *p, t_map *map)
{
	if (key == 'd')
	{
		printf("DIR LEFT\n");
		p->pa += 0.2;
		p->dx = cos(p->pa) * STEP;
		p->dy = sin(p->pa) * STEP;
		printf("dir : {%lf, %lf}\n", p->dx, p->dy);
	}
	if (key == 'a')
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

static int	wall_hit(int mapXidx, int mapYidx, t_ray *ray, t_map *map)
{
	if (mapXidx >= 0 && mapXidx < map->max.x * SCALE_MAP
			&& mapYidx >= 0 && mapYidx < map->max.y * SCALE_MAP)
		return (map->imap[mapYidx][mapXidx]);
	return (false);
	(void)ray;
}

static void	key_correct_path(int key, t_player *p, t_map *map)
{
	int	mapXidx, mapYidx;

	mapXidx = (int)(p->px / map->mapS);
	mapYidx = (int)(p->py / map->mapS);
	if (!wall_hit(mapXidx, mapYidx, NULL, map))
		return ;
	if (key == A_DOWN && p->py < HI - SECURE_STEP)
	{
		p->px -= p->dy;
		p->py -= p->dx;
	}
	else if (key == A_LEFT && p->px > SECURE_STEP)
	{
		p->py -= p->dy;
		p->px += p->dx;
	}
	else if (key == A_RIGHT && p->px < WI - SECURE_STEP)
	{
		p->py += p->dy;
		p->px -= p->dx;
	}
	else if (key == A_UP && p->py > SECURE_STEP)
	{
		p->px += p->dy;
		p->py += p->dx;
	}
}

int	key_update_position(int key, t_data *data, t_player *p)
{
	if (data->menu.is_menu)
		return (1);
	if (key == 'r')
	{
		p->px = 0;
		p->py = 0;
	}
	if (key == A_UP && p->py < HI - SECURE_STEP)
	{
		p->px += p->dx;
		p->py += p->dy;
	}
	else if (key == A_RIGHT && p->px > SECURE_STEP)
	{
		p->py += p->dx;
		p->px -= p->dy;
	}
	else if (key == A_LEFT && p->px < WI - SECURE_STEP)
	{
		p->py -= p->dx;
		p->px += p->dy;
	}
	else if (key == A_DOWN && p->py > SECURE_STEP)
	{
		p->px -= p->dx;
		p->py -= p->dy;
	}
	key_update_direction(key, p, &data->run.map);
	key_correct_path(key, p, &data->run.map);
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
	key_update_position(key, data, &player);
	data->run.player = player;
	if (data->menu.is_menu)
		return (key_menu(key, data));
	return (0);
}

