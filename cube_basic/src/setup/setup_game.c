/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:12:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/18 10:38:20 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "string.h"

void	set_player_pos(t_data *data)
{
	int	x;
	int	y;
	int	x0;
	int	y0;

	y = 0;
	while (y < data->run.map.max.y * SCALE_MAP)
	{
		x = 0;
		while (x < data->run.map.max.x * SCALE_MAP)
		{
			if (data->run.map.imap[y][x] >= PLAYER_POS)
			{
				x0 = x * data->run.map.map_s + MOVE_LIMIT + 10;
				y0 = y * data->run.map.map_s + MOVE_LIMIT + 10;
				break ;
			}
			x++;
		}
		if (x != data->run.map.max.x * SCALE_MAP)
			break ;
		y++;
	}
	data->run.player.py = y0;
	data->run.player.px = x0;
}

void	set_player_dir(t_data *data)
{
	printf("Start angle : %c\n", data->run.player.start);
	if (data->run.player.start == 'N')
		data->run.player.pa = PI;
	if (data->run.player.start == 'S')
		data->run.player.pa = 0;
	if (data->run.player.start == 'E')
		data->run.player.pa = PI / 2;
	if (data->run.player.start == 'W')
		data->run.player.pa = -PI / 2;
}

void	init_map_scale(t_map *map)
{
	int	max_tile_w;
	int	max_tile_h;

	max_tile_w = (int)(WI / (map->max.x));
	max_tile_h = (int)(HI / (map->max.y));
	if (max_tile_w < max_tile_h)
		map->map_s = max_tile_w;
	else
		map->map_s = max_tile_h;
	map->map_s /= SCALE_MAP;
	if (map->map_s < 4)
		map->map_s = 4;
	else if (map->map_s > 64)
		map->map_s = 64;
}

void	init_struct(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WI, HI, "Cub3D");
	data->menu.option = 1;
	data->run.map.max.x += 2;
	data->run.map.max.y += 2;
	init_map_scale(&data->run.map);
	set_player_pos(data);
	init_textures(data);
	set_player_dir(data);
	printf("map S : %d\n", data->run.map.map_s);
}

void	set_up_loops(t_data *data)
{
	mlx_do_key_autorepeaton(data->mlx);
	mlx_key_hook(data->win, key_update_env, data);
	mlx_mouse_hook(data->win, mouse_update_env, data);
	mlx_hook(data->win, CLOSE, 0, close_window, data);
	mlx_hook(data->win, MV_MOUSE, 0, mouse_move, data);
	mlx_loop_hook(data->mlx, compute_frame, data);
}
