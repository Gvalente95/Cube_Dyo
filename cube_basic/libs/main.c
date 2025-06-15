/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 06:04:42 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 12:34:51 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define FOV_ANGLE (60.0 * (M_PI / 180.0))
#define NUM_RAYS WIN_WIDTH
#define TILE_SIZE 64

typedef struct s_texture {
    void    *img;
    int     *pixels;
    int     width;
    int     height;
} t_texture;

typedef struct s_player {
    float x, y;
    float angle;
    float move_speed;
    float rot_speed;
} t_player;

typedef struct s_ray {
    float ray_angle;
    float wall_hit_x;
    float wall_hit_y;
    float distance;
    int   was_hit_vertical;
} t_ray;

typedef struct s_data {
    void *mlx;
    void *win;
    t_player player;
    t_texture textures[4]; // N, S, W, E
    int map[8][9];
    int map_width;
    int map_height;
} t_data;

float normalize_angle(float angle)
{
    while (angle < 0) angle += 2 * M_PI;
    while (angle > 2 * M_PI) angle -= 2 * M_PI;
    return angle;
}

float distance_between_points(float x1, float y1, float x2, float y2)
{
    return sqrtf((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

int map_has_wall_at(t_data *data, float x, float y)
{
    if (x < 0 || x >= data->map_width * TILE_SIZE || y < 0 || y >= data->map_height * TILE_SIZE)
        return 1;
    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);
    return (data->map[map_y][map_x] != 0);
}

t_texture load_texture(t_data *data, char *path)
{
    t_texture tex;
    int bpp, size_line, endian;

    tex.img = mlx_xpm_file_to_image(data->mlx, path, &tex.width, &tex.height);
    if (!tex.img)
    {
        printf("Error: Could not load texture %s\n", path);
        exit(1);
    }
    tex.pixels = (int *)mlx_get_data_addr(tex.img, &bpp, &size_line, &endian);
    return tex;
}
t_ray cast_ray(t_data *data, float ray_angle) {
    t_ray ray;
    ray.ray_angle = normalize_angle(ray_angle);

    // Calculer la direction du rayon
    ray.dx = cos(ray.ray_angle);
    ray.dy = sin(ray.ray_angle);

    // Position initiale du rayon
    ray.rx = data->player.x;
    ray.ry = data->player.y;

    // Calculer la distance jusqu'au premier croisement de grille
    float grid_x = floor(ray.rx / TILE_SIZE) * TILE_SIZE;
    grid_x += (ray.dx > 0) ? TILE_SIZE : 0;
    float grid_y = floor(ray.ry / TILE_SIZE) * TILE_SIZE;
    grid_y += (ray.dy > 0) ? TILE_SIZE : 0;

    float delta_dist_x = fabs(1 / ray.dx);
    float delta_dist_y = fabs(1 / ray.dy);

    float side_dist_x = (ray.dx < 0) ? (ray.rx - grid_x) * delta_dist_x : (grid_x + TILE_SIZE - ray.rx) * delta_dist_x;
    float side_dist_y = (ray.dy < 0) ? (ray.ry - grid_y) * delta_dist_y : (grid_y + TILE_SIZE - ray.ry) * delta_dist_y;

    int step_x = (ray.dx < 0) ? -1 : 1;
    int step_y = (ray.dy < 0) ? -1 : 1;

    int hit = 0;
    int side;

    // Algorithme DDA
    while (!hit) {
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            ray.rx += step_x * TILE_SIZE;
            side = 0;
        } else {
            side_dist_y += delta_dist_y;
            ray.ry += step_y * TILE_SIZE;
            side = 1;
        }

        // Vérifier si le rayon a heurté un mur
        if (map_has_wall_at(data, ray.rx, ray.ry)) {
            hit = 1;
        }
    }

    // Calculer la distance jusqu'au mur
    if (side == 0) {
        ray.wall_hit_x = ray.rx;
        ray.wall_hit_y = ray.ry + (ray.rx - data->player.x) * (ray.dy / ray.dx);
    } else {
        ray.wall_hit_y = ray.ry;
        ray.wall_hit_x = ray.rx + (ray.ry - data->player.y) * (ray.dx / ray.dy);
    }

    ray.distance = distance_between_points(data->player.x, data->player.y, ray.wall_hit_x, ray.wall_hit_y);
    ray.was_hit_vertical = side;

    return ray;
}

t_ray cast_ray(t_data *data, float ray_angle);
int get_texture_x(t_ray *ray, t_texture *tex);
int get_texture_pixel_color(t_texture *tex, int x, int y);

void draw_wall_strip(t_data *data, int strip_id, t_ray *ray, void *img)
{
    float corrected_dist = ray->distance * cos(ray->ray_angle - data->player.angle);
    if (corrected_dist == 0) corrected_dist = 1;
    float proj_plane_dist = (WIN_WIDTH / 2) / tan(FOV_ANGLE / 2);
    int wall_height = (int)((TILE_SIZE / corrected_dist) * proj_plane_dist);

    int top = (WIN_HEIGHT / 2) - (wall_height / 2);
    if (top < 0) top = 0;
    int bottom = (WIN_HEIGHT / 2) + (wall_height / 2);
    if (bottom > WIN_HEIGHT) bottom = WIN_HEIGHT;

    t_texture *tex;
    if (ray->was_hit_vertical)
        tex = (data->player.x < ray->wall_hit_x) ? &data->textures[3] : &data->textures[2];
    else
        tex = (data->player.y < ray->wall_hit_y) ? &data->textures[1] : &data->textures[0];

    int tex_x = get_texture_x(ray, tex);

    for (int y = 0; y < WIN_HEIGHT; y++)
    {
        int color;
        if (y < top)
            color = 0xAAAAAA;
        else if (y > bottom)
            color = 0x444444;
        else
        {
            int tex_y = ((y - top) * tex->height) / wall_height;
            color = get_texture_pixel_color(tex, tex_x, tex_y);
        }
        mlx_pixel_put(data->mlx, data->win, strip_id, y, color);
    }
}

int get_texture_x(t_ray *ray, t_texture *tex)
{
    float hit_coord = ray->was_hit_vertical ? ray->wall_hit_y : ray->wall_hit_x;
    hit_coord /= TILE_SIZE;
    hit_coord -= floor(hit_coord);
    return (int)(hit_coord * tex->width);
}

int get_texture_pixel_color(t_texture *tex, int x, int y)
{
    if (x < 0) x = 0;
    if (x >= tex->width) x = tex->width - 1;
    if (y < 0) y = 0;
    if (y >= tex->height) y = tex->height - 1;
    return tex->pixels[y * tex->width + x];
}

int render(t_data *data)
{
    for (int i = 0; i < WIN_WIDTH; i++)
    {
        float ray_angle = normalize_angle(data->player.angle - FOV_ANGLE / 2 + ((float)i / WIN_WIDTH) * FOV_ANGLE);
        t_ray ray = cast_ray(data, ray_angle);
        draw_wall_strip(data, i, &ray, NULL);
    }
    return 0;
}

int handle_keys(int key, t_data *data)
{
    float new_x = data->player.x;
    float new_y = data->player.y;

    if (key == 65307)
        exit(0);
    if (key == 65362)
    {
        new_x += cos(data->player.angle) * data->player.move_speed;
        new_y += sin(data->player.angle) * data->player.move_speed;
    }
    else if (key == 65364)
    {
        new_x -= cos(data->player.angle) * data->player.move_speed;
        new_y -= sin(data->player.angle) * data->player.move_speed;
    }
    else if (key == 'a')
        data->player.angle = normalize_angle(data->player.angle - data->player.rot_speed);
    else if (key == 'd')
        data->player.angle = normalize_angle(data->player.angle + data->player.rot_speed);

    if (!map_has_wall_at(data, new_x, new_y))
    {
        data->player.x = new_x;
        data->player.y = new_y;
    }

    render(data);
    return 0;
}

int main()
{
    t_data data = {0};
    int map[8][9] = {
        {1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,1},
        {1,0,0,1,1,1,0,0,1},
        {1,0,0,1,0,1,0,0,1},
        {1,0,0,1,0,1,0,0,1},
        {1,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1}
    };
    for (int y = 0; y < 8; y++)
        for (int x = 0; x < 9; x++)
            data.map[y][x] = map[y][x];

    data.map_width = 9;
    data.map_height = 8;
    data.player.x = 300;
    data.player.y = 300;
    data.player.angle = 0;
    data.player.move_speed = 10.0;
    data.player.rot_speed = 0.1;

    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Raycaster With Texture");

    data.textures[0] = load_texture(&data, "textures/north.xpm");
    data.textures[1] = load_texture(&data, "textures/south.xpm");
    data.textures[2] = load_texture(&data, "textures/west.xpm");
    data.textures[3] = load_texture(&data, "textures/east.xpm");

    render(&data);
    mlx_key_hook(data.win, handle_keys, &data);
    mlx_loop(data.mlx);
    return 0;
}

