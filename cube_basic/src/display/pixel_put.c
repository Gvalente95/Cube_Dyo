/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:00:32 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/21 13:24:30 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	create_img(t_data *data)
{
	(void)data;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || y <= 0 || x >= WI || y >= HI)
		return ;
	dst = data->run.frame.addr
		+ (y * data->run.frame.offset + x * (data->run.frame.bpp / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put2(t_data *data, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x >= WI || y >= HI)
        return ;
    if (!data || !data->run.frame2.addr)
        return ;
    dst = data->run.frame2.addr
        + (y * data->run.frame2.offset + x * (data->run.frame2.bpp / 8));
    *(unsigned int*)dst = color;
}
