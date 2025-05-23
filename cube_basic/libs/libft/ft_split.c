/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:30:35 by aseite            #+#    #+#             */
/*   Updated: 2024/10/18 10:58:45 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_c(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static int	gl(char const *s, char c, int start)
{
	int	i;

	i = 0;
	while (s[start] && s[start] != c)
	{
		start++;
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**tab;

	i = 0;
	j = 0;
	k = 0;
	tab = malloc((count_c(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (s[i] && k < count_c(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			tab[k] = malloc((gl(s, c, i) + 1) * sizeof(char));
		while (s[i] && s[i] != c)
			tab[k][j++] = s[i++];
		tab[k++][j] = '\0';
		j = 0;
	}
	tab[k] = NULL;
	return (tab);
}
