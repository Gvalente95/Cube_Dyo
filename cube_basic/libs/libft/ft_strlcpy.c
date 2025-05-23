/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:33:32 by aseite            #+#    #+#             */
/*   Updated: 2024/10/10 20:04:07 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
//#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	j;

	srclen = 0;
	j = 0;
	while (src[srclen])
		srclen++;
	if (size == 0)
		return (srclen);
	while (src[j] && j < size - 1)
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (srclen);
}
/*
int	main()
{
	size_t		size = 4;
	char		dest[4];
	const char	*src = "azeeee";

	printf("%zu \n\n", ft_strlcpy(dest, src, size));
	return (0);
}*/
