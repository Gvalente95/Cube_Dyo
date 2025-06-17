/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:42:55 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/17 16:13:49 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	define_dif(t_point *dif, t_point p0, t_point p1)
{
	if (p0.x < p1.x)
		dif->x = 1;
	else
		dif->x = -1;
	if (p0.y < p1.y)
		dif->y = 1;
	else
		dif->y = -1;
}

static void	update_error_and_point(
	t_point *p, t_point dir, t_point dif, int *err)
{
	int	e2;

	e2 = 2 * (*err);
	if (e2 > -dir.y)
	{
		*err -= dir.y;
		p->x += dif.x;
	}
	if (e2 < dir.x)
	{
		*err += dir.x;
		p->y += dif.y;
	}
}

void	draw_line(t_point p0, t_point p1, t_data *data)
{
	t_point	dir;
	t_point	dif;
	int		err;

	dir.x = abs(p1.x - p0.x);
	dir.y = abs(p1.y - p0.y);
	err = dir.x - dir.y;
	ft_bzero(&dif, sizeof(t_point));
	define_dif(&dif, p0, p1);
	while (true)
	{
		my_mlx_pixel_put(data, p0.x / (data->run.map.map_s / 10), p0.y / (data->run.map.map_s / 10), GREEN);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		update_error_and_point(&p0, dir, dif, &err);
	}
}

static int	get_shaded_color(int base_color, int distance)
{
	int	shade;

	if (base_color != WHITE)
		return (base_color);
	shade = 255 - (distance * 255 / NUM_RAYS);
	if (shade < 0)
		shade = 0;
	if (shade > 255)
		shade = 255;
	return ((shade << 16) | (shade << 8) | shade);
	(void)base_color;
}

void	draw_vertical_line(t_column_draw *cd, int start, int end)
{
	int	shaded_color;

	shaded_color = cd->color;
	if (cd->color == WHITE)
		shaded_color = get_shaded_color(cd->color, cd->distance);
	while (start < end)
	{
		if (start >= 0 && start < HI)
		{
			if (cd->color == WHITE)
				shaded_color = get_shaded_color(cd->color, cd->distance);
			my_mlx_pixel_put2(cd->data, cd->ray, start, shaded_color);
		}
		start++;
	}
}
