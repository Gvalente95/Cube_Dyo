/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:03:32 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 15:16:08 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_tex_drawing(int *start, int *end, float *tex_pos, float step)
{
	if (*start < 0)
	{
		*tex_pos = -*start * step;
		*start = 0;
	}
	if (*end > HI)
		*end = HI;
}

void	draw_textured_line(t_texdraw *d)
{
	t_column_draw	top;
	t_column_draw	bot;
	float	step;
	int		height;
	int		y;

	d->tex->pos = 0;
	height = d->end - d->start;
	step = (float)d->tex->hi / height;
	init_tex_drawing(&d->start, &d->end, &d->tex->pos, step);
	for (y = d->start; y < d->end; y++)
	{
		d->ty = (int)d->tex->pos & (d->tex->hi - 1);
		d->color = d->tex->pixels[d->ty * d->tex->wi + d->tx];
		d->tex->pos += step;
		my_mlx_pixel_put2(d->data, d->ray, y, d->color);
	}
	top = (t_column_draw){d->data, d->ray, d->distance,
		d->data->tokens.color[C_COLOR]};
	bot = (t_column_draw){d->data, d->ray, d->distance,
		d->data->tokens.color[F_COLOR]};
	draw_vertical_line(&top, 0, d->start);
	draw_vertical_line(&bot, d->end, HI);
	(void)d->distance;
}
