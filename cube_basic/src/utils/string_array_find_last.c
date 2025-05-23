/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_find_last.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:24:04 by jvoisard          #+#    #+#             */
/*   Updated: 2025/04/28 09:41:31 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_array.h"

static char	**string_array_find_last(
	char **arr,
	char *pattern,
	bool (*match)(char *, char *)
)
{
	char	**cursor;

	cursor = arr;
	if (!*cursor)
		return (NULL);
	while (*cursor)
		cursor++;
	while (cursor >= arr)
	{
		if (match(pattern, *cursor))
			return (cursor);
		cursor--;
	}
	return (NULL);
}

char	**string_array_find_last_start_with(char **arr, char *pattern)
{
	return (string_array_find_last(arr, pattern, string_match_start_with));
}

char	**string_array_find_last_match(char **arr, char *pattern)
{
	return (string_array_find_last(arr, pattern, string_match));
}
