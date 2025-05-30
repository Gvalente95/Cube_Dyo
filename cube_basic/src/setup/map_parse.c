/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:29:23 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/29 05:15:23 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define OK true
#define KO false

static void	print_map(char **map)
{
	int	i = 0;

	while (map && map[i])
	{
		printf("y : %d : %s\n", i, map[i]);
		i++;
	}
}

static int	count_char(char *doc, int c)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while (doc[i])
		if (doc[i++] == c)
			count++;
	return (count);
}

int	ft_isspace(int c)
{
	return ((c == 32 || (c >= 9 && c <= 13)));
}

void	map_get_format(char **map, t_data *data)
{
	t_point	max;
	t_point	iter;

	ft_bzero(&max, sizeof(t_point));
	ft_bzero(&iter, sizeof(t_point));
	while (map && map[iter.y])
	{
		iter.x = 0;
		while (map[iter.y][iter.x])
			iter.x++;
		if (iter.x > max.x)
			max.x = iter.x;
		iter.y++;
	}
	max.y = iter.y;
	data->run.map.max = max;
}

int	**allocate_scaled_map(t_point max)
{
	int	i;
	int	**smap;

	smap = malloc(sizeof(int *) * (max.y * SCALE_MAP + 1));
	if (!smap)
		return (NULL);
	i = 0;
	while (i < max.y * SCALE_MAP)
	{
		smap[i] = malloc(sizeof(int) * (max.x * SCALE_MAP + 1));
		if (!smap[i])
			return (NULL);
		smap[i][max.x * SCALE_MAP] = INT_MAX;
		i++;
	}
	smap[i] = NULL;
	return (smap);
}

void	format_object(char **map, t_point *original, int *object, char current)
{
	if (ft_isspace(current))
		*object = -1;
	else if (current >= '0' && current <= '9')
		*object = current - '0';
	else if (ft_isalpha(current))
		*object = PLAYER_POS;
	else
		*object = -2;
	(void)original;
	(void)map;
}

void	map_scale_object(int ***scaled_map, char **map, t_point *original)
{
	char	current;
	int		object;
	t_point	scale;
	t_point	iter;

	ft_bzero(&iter, sizeof(t_point));
	scale.x = original->x * SCALE_MAP;
	scale.y = original->y * SCALE_MAP;
	current = map[original->y][original->x];
	format_object(map, original, &object, current);
	while (iter.y < SCALE_MAP)
	{
		iter.x = 0;
		while (iter.x < SCALE_MAP)
		{
			if (object == 1 && (iter.x == 0 || iter.x == SCALE_MAP - 1 || iter.y == 0 || iter.y == SCALE_MAP - 1))
				(*scaled_map)[scale.y + iter.y][scale.x + iter.x++] = object;
			else
				(*scaled_map)[scale.y + iter.y][scale.x + iter.x++] = object;
		}
		iter.y++;
	}
	original->x++;
}

int	**scale_map(char **map, t_data *data)
{
	int		**scaled_map;
	t_point	max;
	t_point	iter;

	ft_bzero(&iter, sizeof(t_point));
	ft_bzero(&max, sizeof(t_point));
	map_get_format(map, data);
	max = data->run.map.max;
	scaled_map = allocate_scaled_map(max);
	if (!scaled_map)
		return (NULL);
	while (iter.y < max.y)
	{
		iter.x = 0;
		while (iter.x < max.x)
			map_scale_object(&scaled_map, map, &iter);
		iter.y++;
	}
	return (scaled_map);
}


bool	check_map(char **map)
{
	(void)map;
	return (OK);
}

char	**parse_map(char *doc)
{
	int		i;
	int		j;
	int		k;
	int		y;
	char	**map;

	i = 0;
	k = 0;
	y = count_char(doc, '\n');
	map = malloc(sizeof(char *) * (y + 1));
	while (doc[i])
	{
		j = 0;
		y = 0;
		while (doc[i + j] && doc[i + j] != '\n')
			j++;
		map[k] = malloc(j + 1);
		while (j-- > 0 && doc[i])
			map[k][y++] = doc[i++];
		map[k++][y] = '\0'; 
		i++;
	}
	map[k] = NULL;
	free(doc);
	print_map(map);
	return (map);
}
