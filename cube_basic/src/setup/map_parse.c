/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:29:23 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/26 12:53:17 by dyodlm           ###   ########.fr       */
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

int	ft_isspace(int c)
{
	return ((c == 32 || (c >= 9 && c <= 13)));
}

void	map_adapt_object(
	int ***scaled_map, char **map,
	t_point *scale, t_point *iter)
{
	if (ft_isspace(map[iter->y][iter->x]))
		*scaled_map[scale->y][scale->x] = -1;
	else
		*scaled_map[scale->y][scale->x] = map[iter->y][iter->x] - '0';
	scale->x++;
}

int	**scale_map(char **map, t_data *data)
{
	int		**scaled_map;
	t_point	max;
	t_point	iter;
	t_point	scale;

	ft_bzero(&iter, sizeof(t_point));
	map_get_format(map, data);
	max = data->run.map.max;
	scaled_map = calloc(sizeof(int *), max.y);
	if (!scaled_map)
		return (free_data(data), NULL);
	while (iter.y < max.y)
	{
		scaled_map[iter.y] = calloc(sizeof(int), max.x * SCALE_MAP + 1);
		while (map[iter.y] && map[iter.y][iter.x])
		{
			scale.y = iter.y * SCALE_MAP;
			scaled_map = calloc(sizeof(int), max.x * SCALE_MAP + 1);
			if (!scaled_map[scale.y])
				return (free_data(data), NULL);
			while (scale.y++ < SCALE_MAP)
			{
				scale.x = iter.x * SCALE_MAP;
				while (scale.x < SCALE_MAP)
					map_adapt_object(&scaled_map, map, &scale, &iter);
			}
			scaled_map[scale.y][scale.x] = INT_MAX;
			iter.x++;
		}
		iter.y++;
	}
	scaled_map[iter.y] = NULL;
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
