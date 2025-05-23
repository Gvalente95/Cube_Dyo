/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_match.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:22:06 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/28 09:55:19 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_array.h"

bool	string_match(char *pattern, char *str)
{
	return (!ft_strncmp(pattern, str, ft_strlen(str)));
}

bool	string_match_start_with(char *pattern, char *str)
{
	while (*pattern && *str)
	{
		if (*pattern != *str)
			return (false);
		str++;
		pattern++;
	}
	if (*pattern && !*str)
		return (false);
	return (true);
}
