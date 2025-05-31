/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 06:35:06 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 06:44:54 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*char	**ft_strplit(char *str, char *split)
{
	char	**splited;

	splited = NULL;
	return (splited);
}*/
#include <stdlib.h>

static int	is_sep(const char *str, const char *sep)
{
	return (ft_strncmp(str, sep, ft_strlen(sep)) == 0);
}

static int	count_parts(const char *str, const char *sep)
{
	int count = 0;
	size_t sep_len = ft_strlen(sep);

	while (*str)
	{
		if (!is_sep(str, sep) && (*str != '\0'))
		{
			count++;
			while (*str && !is_sep(str, sep))
				str++;
		}
		else
			str += sep_len;
	}
	return (count);
}

static char	*str_dup_until(const char *start, const char *end)
{
	size_t	len = end - start;
	char	*word = malloc(len + 1);

	if (!word)
		return (NULL);
	ft_memcpy(word, start, len);
	word[len] = '\0';
	return (word);
}

char	**ft_strsplit(char *str, char *sep)
{
	int		i = 0;
	char	**result;
	char	*start;
	size_t	sep_len = ft_strlen(sep);

	if (!str || !sep || !*sep)
		return (NULL);
	result = malloc((count_parts(str, sep) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (*str)
	{
		if (!is_sep(str, sep) && *str != '\0')
		{
			start = str;
			while (*str && !is_sep(str, sep))
				str++;
			result[i++] = str_dup_until(start, str);
		}
		else
			str += sep_len;
	}
	result[i] = NULL;
	return (result);
}
