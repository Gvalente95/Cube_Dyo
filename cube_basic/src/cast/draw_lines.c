/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:42:55 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 09:46:02 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_line(int x0, int y0, int x1, int y1, t_data *data)
{
	int	dx = abs(x1 - x0);
	int	dy = abs(y1 - y0);
	int	sx = x0 < x1 ? 1 : -1;
	int	sy = y0 < y1 ? 1 : -1;
	int	err = dx - dy;	
	
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

void	draw_vertical_line(t_data *data, int start, int end, int ray, int distance, int color)
{
	int		shade;
	int		shaded_color;

	if (color == WHITE)
	{
		shade = 255 - (distance * 255 / NUM_RAYS);
		if (shade < 0)
			shade = 0;
		if (shade > 255)
			shade = 255;
	}
	else
		shaded_color = color;
	while (start < end)
	{
		if (start >= 0 && start < HI)
		{
			if (color == WHITE)
				shaded_color = (shade << 16) | (shade << 8) | shade;
			my_mlx_pixel_put2(data, ray, start, shaded_color);
		}
		start++;
	}
}

void draw_textured_line(t_data *data, int ray, int start, int end, float distance, t_texture *tex, int tx)
{
	int height = end - start;
	int ty;
	float step = (float)tex->hi / height;
	float tex_pos = 0;
	int color;

	if (start < 0)
	{
		tex_pos = -start * step;
		start = 0;
	}
	if (end > HI)
		end = HI;
	for (int y = start; y < end; y++)
	{
		ty = (int)tex_pos & (tex->hi - 1);
		tex_pos += step;
		color = tex->pixels[ty * tex->wi + tx];
		my_mlx_pixel_put2(data, ray, y, color);
	}
	draw_vertical_line(data, 0, start, ray, distance,
		data->tokens.color[C_COLOR]);
	draw_vertical_line(data, end, HI, ray, distance,
		data->tokens.color[F_COLOR]);
	(void)distance;
}
