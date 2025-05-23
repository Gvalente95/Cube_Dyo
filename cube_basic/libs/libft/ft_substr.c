/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:00:52 by aseite            #+#    #+#             */
/*   Updated: 2024/10/18 16:57:41 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*news;
	size_t		i;
	size_t		s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	news = (char *)malloc((len + 1) * sizeof(char));
	if (!news)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		news[i] = s[start + i];
		i++;
	}
	news[i] = '\0';
	return (news);
}
/*
int	main()
{
	char const *s = "hola";
	unsigned int	start = 2;
	size_t			len = 3;

	s = ft_substr(s, start, len);
	printf("%p\n", s);
	free(s);

	return (0);
}*/
