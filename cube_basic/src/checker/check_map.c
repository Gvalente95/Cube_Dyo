/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:48:45 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 09:14:29 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

#define WALL 1

static bool	invalid_char(int c)
{
	return ((c != 9 && c != 1 && c != -1 && c != 0));
}

static bool	is_closed(t_point max, int **imap, int x, int y)
{
	if (imap[y][x] == WALL)
		return (true);
	if (imap[y][x] == 0)
	{
		if (x <= 0 || y <= 0 || x >= max.x + 1 || y >= max.y + 1)
			return (false);
		if (imap[y - 1][x] == -1 || imap[y + 1][x] == -1 ||
			imap[y][x - 1] == -1 || imap[y][x + 1] == -1)
			return (false);
	}
	return (true);
}

static bool	check_line(t_point max, int **imap, int y, int *player_char)
{
	int	x;

	x = 0;
	while (x < max.x + 2)
	{
		if (!is_closed(max, imap, x, y))
		{
			perror("Error: Map not closed at some point.");
			return (false);
		}
		if (imap[y][x] == 9)
			(*player_char)++;
		if (invalid_char(imap[y][x]))
		{
			perror("Error: Invalid character in map.");
			return (false);
		}
		x++;
	}
	return (true);
}

bool	check_map(t_data *data)
{
	int		player_char;
	int		y;
	t_point	max;

	y = 0;
	player_char = 0;
	max = data->run.map.max;
	while (y < max.y + 2)
	{
		if (!check_line(max, data->run.map.imap, y, &player_char))
			return (false);
		y++;
	}
	if (player_char != 1)
	{
		perror("Error: Invalid number of player start positions.");
		return (false);
	}
	return (true);
}
