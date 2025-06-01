/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:48:45 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 07:15:44 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

#define WALL 1

static bool	closed(t_point max, int **imap, int x, int y)
{
	if (imap[y][x] == WALL)
		return (true);
	else if (imap[y][x] == 0)
	{
		if (y - 1 > 0)
			if (imap[y - 1][x] == -1)
				return (false);
		if (y + 1 < max.y)
			if (imap[y + 1][x] == -1)
		if (x - 1 > 0)
			if (imap[y][x - 1] == -1)
				return (false);
		if (x + 1 < max.x)
			if (imap[y][x + 1] == -1)
				return (false);
		if (x == 0 || y == 0 || x == max.x || y == max.y)
			return (false);
	}
	return (true);
}

static bool	check_line(t_point max, int **imap, int y)
{
	int	x;

	x = 0;
	while (imap[y][x])
	{
		if (!closed(max, imap, x, y))
			return (KO);
		x++;
	}
	return (OK);
}

bool	check_map(t_data *data)
{
	int	y;

	y = 0;
	while (data->run.map.imap[y])
		if (!check_line(data->run.map.max, data->run.map.imap, y++))
				return (perror("Map unclose\n"), KO);
	return (OK);
}
