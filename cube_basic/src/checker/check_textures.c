/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:49:01 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 17:18:22 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	check_doubles(char *doc, t_check list, char *token)
{
	(void)doc;
	(void)list;
	(void)token;
	return (true);
}

bool	check_text_path(t_data *data)
{
	static char	*tokens[] = {"NO", "SO", "EA", "WE"};
	int			i;

	i = 0;
	while (i <= WEST_TEXT)
		if (!check_doubles(data->file, data->check_list, tokens[i++]))
			return (false);
	return (OK);
}
