/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:29:23 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 07:58:27 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void format_object(t_data *data, t_point *original, int *object, char current)
{
	if (!data || !object)
		return;

	if (ft_isspace(current))
		*object = -1;
	else if (current >= '0' && current <= '9')
		*object = current - '0';
	else if (ft_isalpha(current))
	{
		*object = PLAYER_POS;
		if (data)
			data->run.player.start = current;
	}
	else
		*object = -1;
	(void)original;
}

void map_scale_object(int ***scaled_map, char **map, t_point *original, t_data *data)
{
	if (!scaled_map || !*scaled_map || !map || !original || !data)
		return;

	char current = map[original->y][original->x];
	int object;
	t_point scale = { original->x * SCALE_MAP, original->y * SCALE_MAP };

	format_object(data, original, &object, current);

	for (int y = 0; y < SCALE_MAP; y++)
	{
		for (int x = 0; x < SCALE_MAP; x++)
		{
			(*scaled_map)[scale.y + y][scale.x + x] = object;
		}
	}
	original->x++;
}


int **scale_map(char **map, t_data *data)
{
	if (!map || !data)
		return NULL;

	t_point max, iter = {0, 0};

	map_get_format(map, data);
	max = data->run.map.max;

	int **scaled_map = allocate_scaled_map(max);
	if (!scaled_map)
		return NULL;

	for (iter.y = 0; iter.y < max.y; iter.y++)
	{
		iter.x = 0;
		while (iter.x < max.x)
			map_scale_object(&scaled_map, map, &iter, data);
	}
	return scaled_map;
}


char **parse_map(char *doc)
{
	if (!doc)
		return NULL;

	int i = 1, k = 0, line_count = count_char(doc, '\n') - 1;
	char **map = malloc(sizeof(char *) * (line_count + 1));
	if (!map)
		return NULL;

	while (doc[i] && k < line_count)
	{
		int j = 0, y = 0;
		while (doc[i + j] && doc[i + j] != '\n')
			j++;

		if (no_char_in_line(doc, i, i + j))
			break;

		map[k] = malloc(j + 1);
		if (!map[k])
			break;

		while (j-- > 0 && doc[i])
			map[k][y++] = doc[i++];
		map[k++][y] = '\0';
		i++; // skip newline
	}
	map[k] = NULL;
	printf("Let's see\n");
	print_map(map);
	printf("map printed\n");
	free(doc);
	return map;
}

