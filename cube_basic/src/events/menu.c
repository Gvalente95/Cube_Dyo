/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 07:07:46 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/17 16:20:54 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	clean_window(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < WI)
	{
		j = 0;
		while (j < HI)
			my_mlx_pixel_put2(data, i, j++, BLACK);
		i++;
	}
}

void	show_cmds(t_data *data)
{
	(void)data;
}

void	define_action(t_data *data)
{
	if (data->menu.option == 1)
	{
		clean_window(data);
		data->menu.is_menu = 0;
	}
	if (data->menu.option == 2)
		show_cmds(data);
	if (data->menu.option == 3)
		close_window(data);
}

int	key_menu(int key, t_data *data)
{
	if (key == 'q')
		data->menu.is_menu = 0;
	if (key == A_DOWN && data->menu.option < MENU_SLOTS)
		data->menu.option++;
	if (key == A_UP && data->menu.option > 1)
		data->menu.option--;
	if (key == ENTER || key == 'o')
		define_action(data);
	return (0);
}
