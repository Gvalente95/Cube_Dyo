/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:03:03 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 17:56:04 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	key_update_direction(int key, t_player_ *p, t_map *map)
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

#define SECURE_STEP 10

int	key_update_position(int key, t_data *data, t_player_ *p)
{
	if (data->menu.is_menu)
		return (1);
	if (key == A_UP && p->py < HI && data->run.player_.dir_.up)
	{
		p->py += p->dx;
		p->px += p->dy;
	}
	else if (key == A_LEFT && p->px > 0 && data->run.player_.dir_.left)
	{
		p->px += p->dx;
		p->py -= p->dy;
	}
	else if (key == A_RIGHT && p->px < WI && data->run.player_.dir_.right)
	{
		p->px -= p->dx;
		p->py += p->dy;
	}
	else if (key == A_DOWN && p->py > 0 && data->run.player_.dir_.down)
	{
		p->py -= p->dx;
		p->px -= p->dy;
	}
	key_update_direction(key, p, &data->run.map);
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
	check_player_direction(data);
	key_update_position(key, data, &player);
	data->run.player = player;
	if (data->menu.is_menu)
		return (key_menu(key, data));
	return (0);
}
