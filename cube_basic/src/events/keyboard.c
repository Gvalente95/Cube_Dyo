/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:03:03 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/25 08:57:23 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	show_cmds(t_data *data)
{
	(void)data;
}

int	key_update_direction(int key, t_player *p)
{
	if (key == 'a')
	{
		printf("DIR LEFT\n");
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
}

# define SECURE_STEP 10

static void	key_correct_path(int key, t_player *p)
{
	int	mapXidx, mapYidx;
	int	mapX=15, mapY=8, mapS=64;
	int	map[8][15]=
		{
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,1,0,0,1,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,0,1,0,0,0,0,0,0,0,0,1},
			{1,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
			{1,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
			{1,0,0,0,0,1,0,0,0,0,0,1,0,0,1},
			{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};
	
	mapXidx = (int)(p->px / mapS);
	mapYidx = (int)(p->py / mapS);
	if (mapXidx >= 0 && mapXidx < mapX && mapYidx >= 0 && mapYidx < mapY)
	{
		if (map[mapYidx][mapXidx] == 0)// && map[mapYidx * mapX + mapXidx] == 0)
			return ;
	}
	else
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
	if (key == A_DOWN && p->py < HI - SECURE_STEP)
	{
		p->px += p->dy;
		p->py += p->dx;
	}
	else if (key == A_LEFT && p->px > SECURE_STEP)
	{
		p->py += p->dy;
		p->px -= p->dx;
	}
	else if (key == A_RIGHT && p->px < WI - SECURE_STEP)
	{
		p->py -= p->dy;
		p->px += p->dx;
	}
	else if (key == A_UP && p->py > SECURE_STEP)
	{
		p->px -= p->dy;
		p->py -= p->dx;
	}
	key_update_direction(key, p);
	key_correct_path(key, p);
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

void	black(t_data *data, int win)
{
	int	i;
	int	j;

	i = 0;
	while (i < WI)
	{
		j = 0;
		while (j < HI)
		{
			if (win == 1)
				my_mlx_pixel_put(data, i, j, BLACK);
			else
				my_mlx_pixel_put2(data, i, j, BLACK);
			j++;
		}
		i++;
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
	key_update_position(key, data, &player);
	data->run.player = player;
	if (data->menu.is_menu)
		return (key_menu(key, data));
	return (0);
}

