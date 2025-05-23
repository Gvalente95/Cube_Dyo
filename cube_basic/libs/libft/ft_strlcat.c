/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:33:18 by aseite            #+#    #+#             */
/*   Updated: 2024/10/10 19:59:24 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
//#include <stdio.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;
	size_t	destlen;

	destlen = 0;
	srclen = 0;
	i = 0;
	while (dst[destlen] && destlen < size)
		destlen++;
	while (src[srclen])
		srclen++;
	if (destlen >= size)
		return (size + srclen);
	while (src[i] && size - 1 > destlen + i)
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}
/*
int	main()
{
	size_t		len = 3;
	char		dest[3] = "abc";
	const char	*src = "";

	ft_strlcat(dest, src, len);
	return (0);
}*/
