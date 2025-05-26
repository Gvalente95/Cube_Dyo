/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:12:09 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/26 12:50:15 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "string.h"

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_data(data);
	exit(1);
	return (0);
}

static void	int_array_free(int ***array)
{
	t_point	iter;

	ft_bzero(&iter, sizeof(t_point));
	if (!array || !*array)
		return ;
	while (*array[iter.y])
	{
		free(*array[iter.y]);
		iter.y++;
	}
}

void	free_data(t_data *data)
{
	string_array_free(&data->run.map.map);
	int_array_free(&data->run.map.imap);
	if (!data->mlx || !data->win)
		return ;
	if (data->run.frame.img)
		mlx_destroy_image(data->mlx, data->run.frame.img);
	if (data->run.frame2.img)
		mlx_destroy_image(data->mlx_cast, data->run.frame2.img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx_cast, data->win_cast);
	mlx_destroy_display(data->mlx);
	mlx_destroy_display(data->mlx_cast);
	free(data->mlx);
	free(data->mlx_cast);
}

void	exit_game(t_data *data)
{
	printf("Map is shit\n");
	free_data(data);
	exit(EXIT_FAILURE);
	(void)data;
}
