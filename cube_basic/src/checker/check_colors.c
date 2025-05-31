/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:49:16 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 17:20:03 by dyodlm           ###   ########.fr       */
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

bool	check_color_config(t_data *data)
{
	static char	*tokens[] = {"C", "F", "W"};
	int			i;

	i = 0;
	while (i <= W_COLOR)
		if (!check_doubles(data->file, data->check_list, tokens[i++]))
			return (false);
	return (OK);
}
