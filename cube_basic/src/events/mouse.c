/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:02:53 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/08 04:56:08 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	mouse_update_view(int key, int x, int y, t_data *data)
{
	if (data->menu.is_menu)
		return (1);
	(void)x;
	(void)y;
	(void)key;
	(void)data;
	return (0);
}

int	mouse_update_env(int key, int x, int y, t_data *data)
{
	if (data->menu.is_menu)
		return (1);
	(void)x;
	(void)y;
	(void)key;
	(void)data;
	return (0);
}
