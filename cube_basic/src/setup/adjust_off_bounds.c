/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_off_bounds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 07:17:14 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 07:38:45 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int **adjustment(int **map, t_point max)
{
	int     **nmap;
	t_point iter;

	// Allocation du tableau de lignes (+2 pour les bordures haut/bas)
	nmap = malloc((max.y + 2) * sizeof(int *));
	if (!nmap)
		return (NULL);

	for (iter.y = 0; iter.y < max.y + 2; iter.y++)
	{
		nmap[iter.y] = malloc((max.x + 2) * sizeof(int));
		if (!nmap[iter.y])
		{
			// Libération en cas d'échec partiel
			while (--iter.y >= 0)
				free(nmap[iter.y]);
			free(nmap);
			return (NULL);
		}

		for (iter.x = 0; iter.x < max.x + 2; iter.x++)
		{
			// Bordures (haut, bas, gauche, droite)
			if (iter.y == 0 || iter.y == max.y + 1 || iter.x == 0 || iter.x == max.x + 1)
				nmap[iter.y][iter.x] = -1;
			else
				nmap[iter.y][iter.x] = map[iter.y - 1][iter.x - 1];
		}
	}
	return nmap;
}


void	adjust_off_bounds(int ***map, t_point max)
{
	int	**new_map;

	new_map = adjustment(*map, max);
	int_array_free(*map);
	*map = new_map;
}
