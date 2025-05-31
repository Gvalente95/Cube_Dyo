/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:12:09 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 08:15:15 by dyodlm           ###   ########.fr       */
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

static void	int_array_free(int **array)
{
	int	i;

	i = 0;
	if (!array)
		return;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	printf("broke %d\n", i++);
	string_array_free(&data->run.map.map);
	printf("broke %d\n", i++);
	int_array_free(data->run.map.imap);
	printf("broke %d\n", i++);
	if (!data->mlx || !data->win)
		return ;
	printf("broke %d\n", i++);
	if (data->run.frame.img)
		mlx_destroy_image(data->mlx, data->run.frame.img);
	printf("broke %d\n", i++);
	if (data->run.frame2.img)
		mlx_destroy_image(data->mlx_cast, data->run.frame2.img);
	printf("broke %d\n", i++);
//	while (i < NUM_TEXTURES)
//		mlx_destroy_image(data->mlx, data->textures[i++].img);
//	i = 0;
//	while (i < NUM_TEXTURES)
//		free(data->tokens.text_path[i++]);
	printf("broke %d\n", i++);
	mlx_destroy_window(data->mlx, data->win);
	printf("broke %d\n", i++);
	mlx_destroy_window(data->mlx_cast, data->win_cast);
	printf("broke %d\n", i++);
	mlx_destroy_display(data->mlx);
	printf("broke %d\n", i++);
	mlx_destroy_display(data->mlx_cast);
	printf("broke %d\n", i++);
	free(data->mlx);
	printf("broke %d\n", i++);
	free(data->mlx_cast);
	printf("broke %d\n", i++);
}

void	exit_game(t_data *data)
{
	printf("Map is shit\n");
	free_data(data);
	exit(EXIT_FAILURE);
	(void)data;
}
