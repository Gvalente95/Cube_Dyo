/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:12:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/28 05:52:58 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "string.h"

void	init_struct(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_cast = mlx_init();
	data->win = mlx_new_window(data->mlx, WI, HI, "Cub3D");
	data->win_cast = mlx_new_window(data->mlx_cast, WI, HI, "CASTING !!");
	data->menu.option = 1;
	data->run.player.dx = 10;
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
