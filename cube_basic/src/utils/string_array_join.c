/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_join.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:33:28 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/28 09:55:24 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_array.h"

char	*string_array_join(char **arr, char *separator)
{
	t_string	join;

	join.value = NULL;
	if (!arr)
		return (NULL);
	if (*arr)
		string_push_str(&join, *(arr++));
	while (*arr)
	{
		string_push_str(&join, separator);
		string_push_str(&join, *(arr++));
	}
	return (join.value);
}
