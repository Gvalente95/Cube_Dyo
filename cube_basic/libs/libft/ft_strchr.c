/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:31:40 by aseite            #+#    #+#             */
/*   Updated: 2024/10/18 15:58:19 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (!*s)
			return (0);
		s++;
	}
	return ((char *)s);
}
/*
#include <stdio.h>

int	main()
{
	const char	*s = "abcdefg";
	int		c = 122;

	printf("%s \n", ft_strchr(s, c));
	return (0);
}*/
