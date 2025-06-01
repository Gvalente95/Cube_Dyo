/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:50:56 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 13:28:52 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_2d_wall(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = x + 1;
	while (i < x + data->run.map.map_s - 1)
	{
		j = y + 1;
		while (j < y + data->run.map.map_s - 1)
			my_mlx_pixel_put(data, i, j++, color);
		i++;
	}
}

void	draw_2d_map(t_data *data)
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
			else
				color = RED;
			x0 = x * data->run.map.map_s;
			y0 = y * data->run.map.map_s;
			draw_2d_wall(data, x0, y0, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data)
{
	int	x;
	int	y;

	x = data->run.player.px;
	while (x <= (data->run.player.px + PSIZE))
	{
		y = data->run.player.py;
		while (y <= (data->run.player.py + PSIZE))
			my_mlx_pixel_put(data, x, y++, GREEN);
		x++;
	}
}
