/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 07:48:34 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/29 11:08:54 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <stdbool.h>
# include "libft.h"
# include "string.h"
# include "string_array.h"
# include <mlx.h>
# include <math.h>
# include <limits.h>

# include "macros.h"
# include "test.h"

typedef struct s_display
{
	void	*img;
	void	*addr;
	int		bpp;
	int		offset;
	int		endian;
}	t_display;

typedef struct s_long_float_point
{
	double	x;
	double	y;
}	t_dpoint;

typedef struct s_float_point
{
	float	x;
	float	y;
}	t_fpoint;

typedef struct s_bot
{
	short int	speed[3];
	char		pos[3];
}	t_bot;

typedef struct s_direction_ok
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;
}	t_dir;

typedef struct s_player
{
	short int	speed[3];
	float		px;
	float		py;
	float		dx;
	float		dy;
	float		pa;
	t_dir		dir;
	bool		item;
	bool		gun;
}	t_player;

typedef struct s_poinst
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char	**map;
	int		**imap;
	int		mapS;
	t_point	max;
}	t_map;

typedef struct s_ray
{
	float	ra;
	float	rx;
	float	ry;
	int		mapXidx;
	int		mapYidx;
	float	fx_idx;
	float	fy_idx;
	float	dx;
	float	dy;
	int		depth;
	float	step;
	float	distance;
}	t_ray;

typedef struct s_engine
{
	t_display	frame;
	t_display	frame2;
	t_player	player;
	t_bot		*bots;
	t_ray		*ray;
	t_map		map;
//	char		**map;
//	int			**imap;
}	t_engine;

typedef struct s_menu
{
	bool	is_menu;
	char	slot_menu[MENU_SLOTS];
	int		option;
}	t_menu;

typedef struct s_data
{
	t_menu		menu;
	t_engine	run;
	void		*mlx;
	void		*win;
	void		*mlx_cast;
	void		*win_cast;	
	int			key;
}	t_data;

//	SETUP
void	init_struct(t_data *data);
void	set_up_loops(t_data *data);

//	MAP PARSE
char	**parse_map(char *doc);
int		**scale_map(char **map, t_data *data);
bool	check_map(char **map);

//	MOUSE EVENTS
int		mouse_update_env(int key, int x, int y, t_data *data);
int		mouse_update_view(int key, int x, int y, t_data *data);

//	KEY EVENTS
int		key_update_env(int key, t_data *data);
int		key_update_position(int key, t_data *data, t_player *p);

//	GENERAL EVENTS
int		close_window(void *param);
int		mouse_move(int x, int y, t_data *data);
int		compute_frame(void *param);
void	check_player_direction(t_data *data);

//	UTILS
void	exit_game(t_data *data);
void	free_data(t_data *data);

//	RAYCASTING
void	compute_raycast(t_data *data);

//	DISPLAY
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	my_mlx_pixel_put2(t_data *data, int x, int y, int color);
void	draw_line(int x0, int y0, int x1, int y1, int color, t_data *data);
void	draw_2Dwall(t_data *data, int x, int y, int color);
void	draw_2Dmap(t_data *data);
void	draw_player(t_data *data);

//	MENU
int		cast_menu(t_data *data, char place[MENU_SLOTS]);

#endif
