/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:29:23 by dyodlm            #+#    #+#             */
/*   Updated: 2025/04/28 09:22:11 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define OK true
#define KO false

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
	return (map);
}
