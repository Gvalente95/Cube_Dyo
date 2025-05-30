/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:12:07 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/30 08:42:02 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "string.h"

void	set_player_pos(t_data *data)
{
	int	x;
	int	y;
	int	x0;
	int	y0;

	y = 0;
	while (y < data->run.map.max.y * SCALE_MAP)
	{
		x = 0;
		while (x < data->run.map.max.x * SCALE_MAP)
		{
			if (data->run.map.imap[y][x] == PLAYER_POS)
			{	
				x0 = x * data->run.map.mapS + MOVE_LIMIT;// * (int)(SCALE_MAP / 2) + 10 * SCALE_MAP;
				y0 = y * data->run.map.mapS + MOVE_LIMIT;// * (int)(SCALE_MAP / 2) + 10 * SCALE_MAP;
				break ;
			}
			x++;
		}
		if (x != data->run.map.max.x * SCALE_MAP)
			break ;
		y++;
	}
	data->run.player.py = y0;// + data->run.map.mapS;// - SCALE_MAP * 3;// * data->run.map.mapS;
	data->run.player.px = x0;// + data->run.map.mapS;// - SCALE_MAP * 3;// + data->run.map.mapS;
	printf("x0 : %d\ny0 : %d\n", x0, y0);
}

t_texture	load_texture(char *path, t_data *data)
{
	t_texture tex;
	int bpp, sl, endian;

	tex.img = mlx_xpm_file_to_image(data->mlx, path, &tex.wi, &tex.hi);
	if (!tex.img)
	{
		printf("Texture load failed");
		exit(1);
	}
	tex.pixels = (int *)mlx_get_data_addr(tex.img, &bpp, &sl, &endian);
	return tex;
}

void init_textures(t_data *data)
{
//	mlx_xpm_file_to_image();
//	mlx_xpm_to_image();
	data->textures[NORTH] = load_texture("textures/NORTH.xpm", data);
	data->textures[SOUTH] = load_texture("textures/SOUTH.xpm", data);
	data->textures[EAST] = load_texture("textures/EAST.xpm", data);
	data->textures[WEST] = load_texture("textures/WEST.xpm", data);
}

void	init_mapS(t_map *map)
{
	// Calculer le nombre de cases max en X et Y
	int	max_tile_w = (int)(WI / map->max.x);
	int	max_tile_h = (int)(HI / map->max.y);

	// Choisir la taille de case la plus petite pour s'assurer que tout rentre
	map->mapS = (max_tile_w < max_tile_h) ? max_tile_w : max_tile_h;
	map->mapS /= SCALE_MAP;
	// Pour éviter des bugs graphiques, on peut fixer une taille minimum/maximum
	if (map->mapS < 4)
		map->mapS = 4; // trop petit pour être visible
	else if (map->mapS > 64)
		map->mapS = 64; // au-delà, trop gros
}

void	init_struct(t_data *data)
{
	data->mlx = mlx_init();
	data->mlx_cast = mlx_init();
	data->win = mlx_new_window(data->mlx, WI, HI, "Cub3D");
	data->win_cast = mlx_new_window(data->mlx_cast, WI, HI, "CASTING !!");
	data->menu.option = 1;
	data->run.player.dx = 10;
	init_mapS(&data->run.map);
	set_player_pos(data);
	init_textures(data);
	printf("map S : %d\n", data->run.map.mapS);
}

void	set_up_loops(t_data *data)
{
	mlx_do_key_autorepeaton(data->mlx);
	mlx_key_hook(data->win, key_update_env, data);
	mlx_mouse_hook(data->win, mouse_update_env, data);
	mlx_hook(data->win, CLOSE, 0, close_window, data);
	mlx_hook(data->win, MV_MOUSE, 0, mouse_move, data);
	mlx_loop_hook(data->mlx, compute_frame, data);
}
