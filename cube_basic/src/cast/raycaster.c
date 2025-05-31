/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 06:04:42 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 15:00:17 by dyodlm           ###   ########.fr       */
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

/*void cast_length(t_data *data, float distance, int ray)
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
	draw_vertical_line(data, 0, start_y, ray, distance, BLUE);
	draw_vertical_line(data, start_y, end_y, ray, distance, WHITE);
	draw_vertical_line(data, end_y, HI, ray, distance, GREEN);
}*/
static void	assign_values(t_data *data, t_ray *ray, t_point *p0, t_point *p1)
{
	p0->x = data->run.player.px + PSIZE / 2;
	p0->y = data->run.player.py + PSIZE / 2;
	p1->x = (int)ray->rx;
	p1->y = (int)ray->ry;
}

static void	render_wall_column(t_data *data, t_ray *ray, int ray_id)
{
	float		wall_height;
	int			start_y;
	int			end_y;
	t_texdraw	d;

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
	d.tx = (fabs(ray->dx) > fabs(ray->dy)) ? (int)ray->ry % d.tex->wi : (int)ray->rx % d.tex->wi;

draw_textured_line(&d);
}

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
			break;
	}
}

void	raycasting(t_data *data)
{
	t_ray	ray;
	t_point	p0;
	t_point	p1;
	int	r;
	float	ra;

	r = NUM_RAYS;
	ra = data->run.player.pa - (FOV / 2);
	ft_bzero(&p0, sizeof(t_point));
	ft_bzero(&p1, sizeof(t_point));
	while (r > 0)
	{
		trace_single_ray(data, &ray, ra);
		render_wall_column(data, &ray, r);
		assign_values(data, &ray, &p0, &p1);
		draw_line(p0, p1, data);
		ra += FOV / NUM_RAYS;
		r--;
	}
}
