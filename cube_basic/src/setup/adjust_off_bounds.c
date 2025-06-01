/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_off_bounds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 07:17:14 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 09:14:54 by dyodlm           ###   ########.fr       */
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
	for (int y = 0; y < max.y + 1; y++)
	{
		for (int x = 0; x < max.x + 1; x++)
		{
			printf("%3d", imap[y][x]);
		}
		printf("\n");
	}
	printf("Imap printed\n");
}

static int	**adjustment(int **map, t_point max)
{
	int		**nmap;
	t_point	iter;

	nmap = malloc(sizeof(int *) * (max.y + 3));
	if (!nmap)
		return (NULL);
	nmap[max.y + 2] = NULL;
	iter.y = 0;
	while (iter.y < max.y + 2)
	{
		nmap[iter.y] = malloc(sizeof(int) * (max.x + 3));
		if (!nmap[iter.y])
		{
			while (--iter.y >= 0)
				free(nmap[iter.y]);
			free(nmap);
			return (NULL);
		}
		iter.x = 0;
		while (iter.x < max.x + 2)
		{
			if (iter.y == 0 || iter.y == max.y + 1 ||
				iter.x == 0 || iter.x == max.x + 1)
				nmap[iter.y][iter.x] = -1;
			else
				nmap[iter.y][iter.x] = map[iter.y - 1][iter.x - 1];
			iter.x++;
		}
		iter.y++;
	}
	return (nmap);
}


void	adjust_off_bounds(int ***map, t_point max)
{
	int	**new_map;

	new_map = adjustment(*map, max);
	if (!new_map)
	{
		perror("Error: Failed to adjust map bounds.");
		return;
	}
	printf("max x : %d\nmax y : %d\n", max.x, max.y);
	print_imap(new_map, max);
	int_array_free(*map);
	*map = new_map;
}
