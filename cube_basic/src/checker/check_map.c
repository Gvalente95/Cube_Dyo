/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:48:45 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 09:01:45 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

#define WALL 1

static bool	invalid_char(int c)
{
	return ((c != 9 && c != 1 && c != -1 && c != 0));
}

static bool closed(t_point max, int **imap, int x, int y)
{
	if (imap[y][x] == WALL)
		return (true);
	if (imap[y][x] == 0)
	{
		if (x == 0 || y == 0 || x >= max.x - 1 || y >= max.y - 1)
			return (false);
		if (imap[y - 1][x] == -1 || imap[y + 1][x] == -1 ||
			imap[y][x - 1] == -1 || imap[y][x + 1] == -1)
			return (false);
	}
	return (true);
}

static bool check_line(t_point max, int **imap, int y, int *player_char)
{
	int	x;

	x = 0;
	while (x < max.x)
	{
		if (!closed(max, imap, x, y))
			return (perror("Map Unclosed bitch got you\n"), KO);
		if (imap[y][x] == 9)
			*player_char += 1;
		if (invalid_char(imap[y][x]))
			return (perror("Invalid char in map\n"), KO);
		x++;
	}
	return (OK);
}

bool check_map(t_data *data)
{
	int		player_char;
	int		y;
	t_point	max;
	
	y = 0;
	player_char = 0;
	max = data->run.map.max;
	while (y < max.y)
	{
		if (check_line(max, data->run.map.imap, y, &player_char) == KO)
		{
			free_data(data);
			exit(EXIT_FAILURE);
			return (false);
		}
		y++;
	}
	if (player_char == 0 || player_char >= 2)
		return (perror("Problem player in map\n"), free_data(data), exit(1), KO);
	return (true);
}
