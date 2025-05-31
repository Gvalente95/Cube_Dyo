/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:42:55 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 13:36:00 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	define_scale(t_point *scale, t_point p0, t_point p1)
{
	if (p0.x < p1.x)
		scale->x = 1;
	else
		scale->x = -1;
	if (p0.y < p1.y)
		scale->y = 1;
	else
		scale->y = -1;
}

void	draw_line(t_point p0, t_point p1, t_data *data)
{
	t_point	dir;
	t_point	scale;
	int		err;
	int		e2;

	dir.x = abs(p1.x - p0.x);
	dir.y = abs(p1.y - p0.y);
	err = dir.x - dir.y;
	ft_bzero(&scale, sizeof(t_point));
	define_scale(&scale, p0, p1);
	while (1)
	{
		my_mlx_pixel_put(data, p0.x, p0.y, GREEN);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dir.y)
		{
			err -= dir.y;
			p0.x += scale.x;
		}
		if (e2 < dir.x)
		{
			err += dir.x;
			p0.y += scale.y;
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
