/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:17:03 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 10:19:31 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	is_sep(const char *str, const char *sep)
{
	return (ft_strncmp(str, sep, ft_strlen(sep)) == 0);
}

static int	count_parts(const char *str, const char *sep)
{
	int		count;
	size_t	sep_len;

	count = 0;
	sep_len = ft_strlen(sep);
	while (*str)
	{
		if (!is_sep(str, sep))
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
	size_t	len;
	char	*word;

	len = end - start;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, start, len);
	word[len] = '\0';
	return (word);
}

static void	split(char **str, char *sep, char ***result)
{
	int		i;
	size_t	sep_len;
	char	*start;

	i = 0;
	sep_len = ft_strlen(sep);
	while (**str)
	{
		if (!is_sep(*str, sep))
		{
			start = *str;
			while (**str && !is_sep(*str, sep))
				(*str)++;
			(*result)[i++] = str_dup_until(start, *str);
		}
		else
			*str += sep_len;
	}
	(*result)[i] = NULL;
}

char	**ft_strsplit(char *str, char *sep)
{
	char	**result;
	int		count;

	if (!str || !sep || !*sep)
		return (NULL);
	count = count_parts(str, sep);
	result = malloc((count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	split(&str, sep, &result);
	return (result);
}
