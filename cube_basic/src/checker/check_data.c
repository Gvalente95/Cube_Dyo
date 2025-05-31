/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:15:00 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 17:48:22 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	is_in_file(char *doc, t_check *list, char *token)
{
	//	Allright for the colors
	//	check for paths
	(void)doc;
	(void)list;
	(void)token;
	return (true);
}

static bool	is_in_double(char *doc, t_check *list, char *token)
{
	//	ALL TODO
	(void)doc;
	(void)list;
	(void)token;
	return (true);
}

static bool	is_format_ok(char *doc, t_check *list, char *token)
{
	//	Allright for colors
	//	check if not empty for paths
	(void)doc;
	(void)list;
	(void)token;
	return (true);
}

static bool	check_tokens(t_data *data)
{
	static char	*tokens[] = {"NO", "SO", "EA", "WE", "F", "W", "C"};
	int			i;

	i = 0;
	while (i < NO_TOKEN)
	{
		if (!is_in_file(data->file, &data->check_list, tokens[i]))
			break ;
		if (!is_in_double(data->file, &data->check_list, tokens[i]))
			break ;
		if (is_format_ok(data->file, &data->check_list, tokens[i++]))
			break ;		
	}
	return (OK);
}

void	check_data(t_data *data)
{
	int	i;

	i = 0;
	if (check_tokens(data) == KO)
		perror("Error with config file content\n");
	if (check_map(data) == KO)
		perror("Error Parsing map :\n");
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
