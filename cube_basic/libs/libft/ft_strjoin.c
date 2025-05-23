/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:32:55 by aseite            #+#    #+#             */
/*   Updated: 2024/10/18 16:09:07 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	getlen(char const *s1, char const *s2)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (s1[i])
		i++;
	len = i;
	i = 0;
	while (s2[i])
		i++;
	len = len + i;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len;
	unsigned int	i;
	char			*news;

	i = 0;
	len = getlen(s1, s2) + 1;
	news = (char *)malloc(len * sizeof(char));
	if (!news)
		return (NULL);
	if (s1[0] == '\0' && s2[0] == '\0')
	{
		news[0] = '\0';
		return (news);
	}
	while (s1[i])
	{
		news[i] = s1[i];
		i++;
	}
	len = i;
	i = 0;
	while (s2[i])
		news[len++] = s2[i++];
	news[len] = '\0';
	return (news);
}
/*
int	main()
{
	char	*s1 = "";
	char	*s2 = "";

	printf("%s \n", ft_strjoin(s1, s2));
	return (0);
}*/
