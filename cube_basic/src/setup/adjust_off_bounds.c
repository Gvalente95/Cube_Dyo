/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_off_bounds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 07:17:14 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 07:56:31 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	print_imap(int **imap, t_point max)
{
	if (!imap)
	{
		printf("Map vide ou non initialisée.\n");
		return;
	}

	for (int y = 0; y < max.y; y++)
	{
		for (int x = 0; x < max.x; x++)
		{
			printf("%3d", imap[y][x]);
		}
		printf("\n");
	}
	printf("Imap printed\n");
}

static int **adjustment(int **map, t_point max)
{
	int     **nmap;
	t_point iter;

	nmap = malloc((max.y + 2) * sizeof(int *));
	if (!nmap)
		return (NULL);

	for (iter.y = 0; iter.y < max.y + 2; iter.y++)
	{
		nmap[iter.y] = malloc((max.x + 2) * sizeof(int));
		if (!nmap[iter.y])
		{
			while (--iter.y >= 0)
				free(nmap[iter.y]);
			free(nmap);
			return (NULL);
		}
		for (iter.x = 0; iter.x < max.x + 2; iter.x++)
		{
			if (iter.y == 0 || iter.y == max.y + 1 || iter.x == 0 || iter.x == max.x + 1)
				nmap[iter.y][iter.x] = -1;
			else
				nmap[iter.y][iter.x] = map[iter.y - 1][iter.x - 1];
		}
	}
	print_imap(nmap, max);
	return (nmap);
}

void	adjust_off_bounds(int ***map, t_point max)
{
	int	**new_map;

	new_map = adjustment(*map, max);
	int_array_free(*map);
	*map = new_map;
}
