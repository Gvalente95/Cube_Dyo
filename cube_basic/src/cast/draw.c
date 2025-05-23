/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 08:50:56 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/17 10:06:10 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*void	draw_line(int x0, int y0, int x1, int y1, t_data *data)
{
	int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(data, x0, y0, GREEN);
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

void	draw_2Dwall(t_data *data, int x, int y, int color)
{
	for (int i = x + 1; i < x + mapS - 1; i++)
		for (int j = y + 1; j < y + mapS - 1; j++)
			my_mlx_pixel_put(data, i, j, color);
}

void	draw_2Dmap(t_data *data)
{
	int	x, y, x0, y0, color;

	for (y = 0; y < mapY; y++)
	{
		for (x = 0; x < mapX; x++)
		{
			if (map[y * mapX + x] == 1)
				color = WHITE;
			else
				color = RED;
			x0 = x * mapS;
			y0 = y * mapS;
			draw_2Dwall(data, x0, y0, color);
		}
	}
}

void	draw_player(t_data *data)
{
	if (data->run.player.px == 0)
	{
		data->run.player.px = 220;
		data->run.player.py = 220;
	}
	for (int x = data->run.player.px; x <= data->run.player.px + PSIZE; x++)
		for (int y = data->run.player.py; y <= data->run.player.py + PSIZE; y++)
			my_mlx_pixel_put(data, x, y, BLUE);
}*/
