/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:42:55 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 12:52:35 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_line(t_point p0, t_point p1, t_data *data)//int x0, int y0, int x1, int y1, t_data *data)
{
//	t_point	dir;
//	t_point	scale;
	int	dx = abs(p1.x - p0.x);
	int	dy = abs(p1.y - p0.y);
	int	sx = p0.x < p1.x ? 1 : -1;
	int	sy = p0.y < p1.y ? 1 : -1;
	int	err = dx - dy;	
	
//	ft_bzero(&dir, sizeof(t_point));
//	ft_bzero(&scale, sizeof(t_point));
//	assign_values(dir, )
	while (1)
	{
		my_mlx_pixel_put(data, p0.x, p0.y, GREEN);
		if (p0.x == p1.x && p0.y == p1.y)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			p0.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			p0.y += sy;
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
