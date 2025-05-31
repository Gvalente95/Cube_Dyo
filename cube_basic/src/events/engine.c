/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:28:27 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 10:47:15 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	mouse_move(int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	(void)data;
	return (0);
}

void	init_display(t_display *frame, void *mlx)
{
	frame->img = mlx_new_image(mlx, WI, HI);
	if (!frame->img)
	{
		perror("mlx_new_image failed");
		exit(EXIT_FAILURE);
	}
	frame->addr = mlx_get_data_addr(
			frame->img, &frame->bpp, &frame->offset, &frame->endian);
	if (!frame->addr)
	{
		perror("mlx_get_data_addr failed");
		exit(EXIT_FAILURE);
	}
}

static void	put_strings(t_data *data)
{
	static char	*options[] = {
		"RESUME GAME", "SHOW COMMANDS", "EXIT GAME", NULL};

	mlx_string_put(data->mlx,
		data->win, WI / 2 - WI / 8, 3000 / (HI / 20) + HI / 2 - 15,
		BLACK, options[0]);
	mlx_string_put(data->mlx, data->win,
		WI / 2 - WI / 8, 4000 / (HI / 20) + HI / 2 - 15,
		BLACK, options[1]);
	mlx_string_put(data->mlx,
		data->win, WI / 2 - WI / 8, 5000 / (HI / 20) + HI / 2 - 15,
		BLACK, options[2]);
}

void	cast_game(t_data *data)
{
	draw_2Dmap(data);
	draw_player(data);
	raycasting(data);
	check_player_direction(data);
}

int	compute_frame(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data || !data->mlx || !data->win)
		return (1);
	if (!data->run.frame.img)
		init_display(&data->run.frame, data->mlx);
	if (!data->run.frame2.img)
		init_display(&data->run.frame2, data->mlx_cast);
	if (!data->menu.is_menu)
		cast_game(data);
	else
		cast_menu(data, data->menu.slot_menu);
	mlx_put_image_to_window(data->mlx, data->win,
		data->run.frame.img, 0, 0);
	mlx_put_image_to_window(data->mlx_cast, data->win_cast,
		data->run.frame2.img, 0, 0);
	if (data->menu.is_menu)
		put_strings(data);
	return (0);
}
