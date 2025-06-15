/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:28:27 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 04:49:53 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		printf("y : %d : %s\n", i, map[i]);
		i++;
	}
}

int	count_char(char *doc, int c)
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
