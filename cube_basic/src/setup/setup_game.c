/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:12:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/28 13:30:04 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "string.h"

void	set_player_pos(t_data *data)
{
	t_point	pos;
	int		stop;

	stop = 0;
	for (int i = 0; i < data->run.map.max.y * SCALE_MAP && !stop; i++)
	{
		for (int j = 0; j < data->run.map.max.x * SCALE_MAP; j++)
		{
			if (data->run.map.imap[i][j] == 9)
			{
				pos.x = j;
				pos.y = i;
				stop = 1;
				break ;
			}
		}
	}
	data->run.player.py = pos.y * SCALE_MAP;
	data->run.player.px = pos.x * SCALE_MAP;
	printf("pos x : %d\npos y : %d\n", pos.x, pos.y);
}

void	init_struct(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_cast = mlx_init();
	data->win = mlx_new_window(data->mlx, WI, HI, "Cub3D");
	data->win_cast = mlx_new_window(data->mlx_cast, WI, HI, "CASTING !!");
	data->menu.option = 1;
	set_player_pos(data);
	data->run.player.dx = 10;
	data->run.map.mapS = (int)(data->run.map.max.x * data->run.map.max.y / SCALE_MAP * 2 / 4);
	printf("map S : %d\n", data->run.map.mapS);
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
