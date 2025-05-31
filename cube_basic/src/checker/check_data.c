/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:15:00 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 16:18:31 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_data(t_data *data)
{
	int	i;

	i = 0;
	if (check_map(data) == KO)
		perror("Error Parsing map :\n");
	if (check_text_path(data) == KO)
		perror("Error Parsing textures :\n");
	if (check_color_config(data) == KO)
		perror("Error Parsing color configuration : \n");
	free(data->file);
	data->file = NULL;
	if (!data->error)
		return ;
	while (data->error[i])
	{
		perror(data->error[i]);
		free(data->error[i++]);
	}
	free(data->error);	
	free_data(data);
	exit(EXIT_FAILURE);
}
