/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_array_find.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:24:04 by jvoisard          #+#    #+#             */
/*   Updated: 2025/02/14 11:43:51 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_array.h"

static char	**string_array_find(
	char **arr,
	char *pattern,
	bool (*match)(char *, char *)
)
{
	while (*arr)
	{
		if (match(pattern, *arr))
			return (arr);
		arr++;
	}
	return (NULL);
}

char	**string_array_find_start_with(char **arr, char *pattern)
{
	return (string_array_find(arr, pattern, string_match_start_with));
}

char	**string_array_find_match(char **arr, char *pattern)
{
	return (string_array_find(arr, pattern, string_match));
}
