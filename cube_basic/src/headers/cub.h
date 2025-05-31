/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 07:48:34 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 09:17:00 by dyodlm           ###   ########.fr       */
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
	char		start;
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

typedef struct s_textures
{
	void	*img;
	int		*pixels;
	int		wi;
	int		hi;
}	t_texture;

typedef struct s_engine
{
	t_display	frame;
	t_display	frame2;
	t_player	player;
	t_bot		*bots;
	t_map		map;
}	t_engine;

typedef struct s_menu
{
	bool	is_menu;
	char	slot_menu[MENU_SLOTS];
	int		option;
}	t_menu;

# define NUM_TEXTURES 4

typedef enum e_text_type
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	e_text_type;

typedef struct s_color
{
	int	R;
	int	G;
	int	B;
}	t_color;

typedef enum e_tokens
{
	NORTH_TEXT,
	SOUTH_TEXT,
	EAST_TEXT,
	WEST_TEXT,
	FLOOR_COLOR,
	SKY_COLOR,
	WALL_COLOR,
	NO_TOKEN
}	e_tokens;

typedef enum e_object_to_paint
{
	F_COLOR,
	C_COLOR,
	W_COLOR
}	e_topaint;

# define OBJS_TO_PAINT 3

typedef struct s_tokens
{
	t_color		color_objects[OBJS_TO_PAINT];
	int			color[OBJS_TO_PAINT];
	char		*text_path[NUM_TEXTURES];	
}	t_tokens;

typedef struct s_data
{
	t_menu		menu;
	t_engine	run;
	t_tokens	tokens;
	t_texture	textures[NUM_TEXTURES];
	void		*mlx;
	void		*win;
	void		*mlx_cast;
	void		*win_cast;	
	int			key;
}	t_data;

//	SETUP
void		init_struct(t_data *data);
void		set_up_loops(t_data *data);
void		init_textures(t_data *data);

//	FILE PARSE
void		parse_metadata(t_data *data, char **doc);
char		**parse_map(char *doc);
int			**scale_map(char **map, t_data *data);
bool		check_map(char **map);

//	MOUSE EVENTS
int			mouse_update_env(int key, int x, int y, t_data *data);
int			mouse_update_view(int key, int x, int y, t_data *data);

//	KEY EVENTS
int			key_update_env(int key, t_data *data);
int			key_update_position(int key, t_data *data, t_player *p);

//	GENERAL EVENTS
int			close_window(void *param);
int			mouse_move(int x, int y, t_data *data);
int			compute_frame(void *param);

//	UTILS
void		exit_game(t_data *data);
void		free_data(t_data *data);

//	RAYCASTING
void		compute_raycast(t_data *data);
void		check_player_direction(t_data *data);
t_texture	load_texture(char *path, t_data *data);

//	MATH
int			extract_length(t_data *data, int x, int  y);

//	DISPLAY
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		my_mlx_pixel_put2(t_data *data, int x, int y, int color);
void		draw_line(int x0, int y0, int x1, int y1, t_data *data);
void		draw_2Dwall(t_data *data, int x, int y, int color);
void		draw_2Dmap(t_data *data);
void		draw_player(t_data *data);
//void	draw_textured_line(t_data *data, t_ray *ray, t_point interval, float distance, a);

//	MENU
int			cast_menu(t_data *data, char place[MENU_SLOTS]);

//	UTILS
char		**ft_strsplit(char *str, char *sep);
int			ft_isspace(int c);

#endif
