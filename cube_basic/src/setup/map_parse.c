/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:29:23 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 08:56:53 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define OK true
#define KO false

bool	no_char_in_line(char *doc, int start, int end)
{
	while (start < end)
	{
		if (ft_isalpha(doc[start]) || ft_isalnum(doc[start]))
			return (false);
		start++;
	}
	return (true);
}
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

void	format_object(t_data *data, t_point *original, int *object, char current)
{
	if (ft_isspace(current))
		*object = -1;
	else if (current >= '0' && current <= '9')
		*object = current - '0';
	else if (ft_isalpha(current))
	{
		*object = PLAYER_POS;
		data->run.player.start = current;
	}
	else
		*object = -2;
	(void)original;
}

void	map_scale_object(int ***scaled_map, char **map, t_point *original, t_data *data)
{
	char	current;
	int		object;
	t_point	scale;
	t_point	iter;

	ft_bzero(&iter, sizeof(t_point));
	scale.x = original->x * SCALE_MAP;
	scale.y = original->y * SCALE_MAP;
	current = map[original->y][original->x];
	format_object(data, original, &object, current);
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
			map_scale_object(&scaled_map, map, &iter, data);
		iter.y++;
	}
	return (scaled_map);
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
	y = count_char(doc, '\n') - 1;
	map = malloc(sizeof(char *) * (y + 1));
	i++;
	while (doc && doc[i])
	{
		j = 0;
		y = 0;
		while (doc[i + j] && doc[i + j] != '\n')
			j++;
		if (no_char_in_line(doc, i, i + j))
			break ;
		map[k] = malloc(j + 1);
		while (j-- > 0 && doc[i] && map[k])
			map[k][y++] = doc[i++];
		map[k++][y] = '\0'; 
		i++;
	}
	free(map[k]);
	map[k] = NULL;
	free(doc);
	printf("UIUIU\n");
	print_map(map);
	printf("MAP PRINTED\n");
	return (map);
}
