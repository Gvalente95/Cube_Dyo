/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 07:55:48 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 08:56:50 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
/*
size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}*/

int	ft_atohx(char *n)
{
	int	nb;
	int	nhx;

	nb = ft_atoi(n);
	return (nb);
	nhx = nb / 16 + nb % 16;
	return (nhx);
}

void	ft_suppress(char **content, char *to_suppress)
{
	int		i;
	char	**split;
	char	*join;

	i = 2;
	if (!content || !*content)
		return ;
	split = ft_strsplit(*content, to_suppress);
	if (!split)
		return ;
	join = ft_strjoin(split[0], split[1]);
	while (split[i])
		join = ft_strjoin(join, split[i++]);
	free(*content);
	*content = join;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*copy_from(char **str, size_t here)
{
	char	*copy;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(*str) - here + 1;
	copy = malloc(len);
	while ((*str)[i + here])
	{
		copy[i] = (*str)[i + here];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	ft_isspace(int c)
{
	return ((c <= 13 && c >= 9) || c == 32);
}
