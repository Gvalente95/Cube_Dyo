/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 09:36:49 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 09:42:13 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_strstr(char *str, char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*to_find)
		return (str);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while (to_find[j] && str[i + j]
			&& i + j < len && str[i + j] == to_find[j])
		{
			if (!to_find[j])
				return (&str[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*ft_strrstr(char *str, char *to_find, size_t len)
{
	size_t	i;

	if (!*to_find)
		return (str + len);
	i = len;
	while (i > 0)
	{
		if (i >= ft_strlen(to_find)
			&& !ft_strncmp(&str[i - ft_strlen(to_find)],
				to_find, ft_strlen(to_find)))
			return (&str[i - ft_strlen(to_find)]);
		i--;
	}
	return (NULL);
}
