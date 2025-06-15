/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 06:04:42 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/15 06:43:31 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include "cub.h"

int	extract_length(t_data *data, int x, int y)
{
	float	dx;
	float	dy;

	dx = x - data->run.player.px;
	dy = y - data->run.player.py;
	return (sqrt(dx * dx + dy * dy));
}

void	draw_vertical_line_(t_data *data,
	int start,
	int end,
	int ray,
	int distance,
	int color)
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
			else
				shaded_color = color;
			my_mlx_pixel_put2(data, ray, start, shaded_color);
		}
		start++;
	}
}

void	cast_length(t_data *data, float distance, int ray)
{
	float	wall_height;
	int		start_y;
	int		end_y;

	wall_height = PROJECTION_CONSTANT / (distance * 3);
	start_y = HI / 2 - wall_height / 2;
	end_y = HI / 2 + wall_height / 2;
	if (start_y < 0)
		start_y = 0;
	if (end_y > HI)
		end_y = HI;
	draw_vertical_line_(data, 0, start_y, ray, distance,
		data->tokens.color[C_COLOR]);
	draw_vertical_line_(data, start_y, end_y, ray, distance, WHITE);
	draw_vertical_line_(data, end_y, HI, ray, distance,
		data->tokens.color[F_COLOR]);
}

//static void	assign_values(t_data *data,
	//t_ray *ray, t_point *p0, t_point *p1)
//{
//	p0->x = data->run.player.px + PSIZE / 2;
//	p0->y = data->run.player.py + PSIZE / 2;
//	p1->x = (int)ray->rx;
//	p1->y = (int)ray->ry;
//}

/*static void	render_wall_column(t_data *data, t_ray *ray, int ray_id)
{
	float		wall_height;
	int			start_y;
	int			end_y;
	t_texdraw	d;

	ft_memset(&d, 0, sizeof(t_texdraw));
	ray->distance = extract_length(data, ray->rx, ray->ry);
	if (ray->distance == 0)
		ray->distance = 1;
	wall_height = PROJECTION_CONSTANT / (ray->distance * 3);
	start_y = HI / 2 - wall_height / 2;
	end_y = HI / 2 + wall_height / 2;
	d.data = data;
	d.ray = ray_id;
	d.start = start_y;
	d.end = end_y;
	d.distance = ray->distance;
	d.tex = select_texture(data, ray);
	if (fabs(ray->dx) > fabs(ray->dy))
		d.tx = (int)ray->ry % d.tex->wi;
	else
		d.tx = (int)ray->rx % d.tex->wi;
	draw_textured_line(&d);
}*/

static void	trace_single_ray(t_data *data, t_ray *ray, float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	else if (angle > 2 * PI)
		angle -= 2 * PI;
	ray->ra = angle;
	adjust_ray_data(ray, data);
	ray->depth = 0;
	while (ray->depth++ < 1000)
	{
		update_ray_pos(ray, &data->run.map);
		if (wall_hit(ray->mapx_idx, ray->mapy_idx, ray, &data->run.map))
			break ;
	}
}

void	raycasting(t_data *data)
{
	t_ray	ray;
	t_point	p0;
	t_point	p1;
	int		r;
	float	ra;

	r = NUM_RAYS;
	ra = data->run.player.pa - (FOV / 2);
	ft_bzero(&p0, sizeof(t_point));
	ft_bzero(&p1, sizeof(t_point));
	while (r > 0)
	{
		trace_single_ray(data, &ray, ra);
		ray.distance = extract_length(data, ray.rx, ray.ry);
		cast_length(data, ray.distance, r--);
		p0.x = data->run.player.px + PSIZE / 2;
		p0.y = data->run.player.py + PSIZE / 2;
		p1.x = (int)ray.rx;
		p1.y = (int)ray.ry;
		draw_line(p0, p1, data);
		ra += FOV / NUM_RAYS;
		r--;
	}
}
