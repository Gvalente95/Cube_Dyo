/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:33:25 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 16:59:09 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_texture	load_texture(char *path, t_data *data)
{
	t_texture	tex;
	int			bpp;
	int			sl;
	int			endian;

	tex.img = mlx_xpm_file_to_image(data->mlx, path, &tex.wi, &tex.hi);
	if (!tex.img)
	{
		printf("Error : Texture load failed");
		free_data(data);
		exit(1);
	}
	tex.pixels = (int *)mlx_get_data_addr(tex.img, &bpp, &sl, &endian);
	return (tex);
}

void	init_textures(t_data *data)
{
	data->textures[NORTH] = load_texture(data->tokens.text_path[NORTH], data);
	data->textures[SOUTH] = load_texture(data->tokens.text_path[SOUTH], data);
	data->textures[EAST] = load_texture(data->tokens.text_path[EAST], data);
	data->textures[WEST] = load_texture(data->tokens.text_path[WEST], data);
}
