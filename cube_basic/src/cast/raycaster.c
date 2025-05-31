/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 06:04:42 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 12:49:39 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include "cub.h"

int	extract_length(t_data *data, int x, int  y)
{
	float	dx;
	float	dy;

	dx = x - data->run.player.px;
	dy = y - data->run.player.py;
	return (sqrt(dx * dx + dy * dy));
}

void cast_length(t_data *data, float distance, int ray)
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
}

/*static void	apply_texture(t_data *data, t_ray *ray)
{
	(void)ray;
	(void)data;
}*/

void raycasting(t_data *data)
{
	t_ray ray;
	int r;
	float distance;
	float step = FOV / NUM_RAYS;
	float ra = data->run.player.pa - (FOV / 2);

	r = NUM_RAYS;
	while (r > 0)
	{
		if (ra < 0)
			ra += 2 * PI;
		else if (ra > 2 * PI)
			ra -= 2 * PI;
		ray.ra = ra;
		adjust_ray_data(&ray, data);
		ray.depth = 0;
		while (ray.depth++ < 1000)
		{
			update_ray_pos(&ray, &data->run.map);
			if (wall_hit(ray.mapx_idx, ray.mapy_idx, &ray, &data->run.map))
				break;
		}
		distance = extract_length(data, ray.rx, ray.ry);
		float wall_height = PROJECTION_CONSTANT / (distance * 3);
		int start_y = HI / 2 - wall_height / 2;
		int end_y = HI / 2 + wall_height / 2;
		t_texture *tex = select_texture(data, &ray);
		int tx = (fabs(ray.dx) > fabs(ray.dy)) ? (int)ray.ry % tex->wi : (int)ray.rx % tex->wi;
		draw_textured_line(data, r, start_y, end_y, distance, tex, tx);
		draw_line(data->run.player.px + PSIZE / 2,
			  data->run.player.py + PSIZE / 2,
			  (int)ray.rx, (int)ray.ry, data);
		ra += step;
		r--;
	}
}
