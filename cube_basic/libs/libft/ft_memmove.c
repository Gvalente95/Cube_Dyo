/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:28:42 by aseite            #+#    #+#             */
/*   Updated: 2024/10/10 19:28:54 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	if (s < d && s + n > d)
	{
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}
/*
int	main()
{
	char		d[10];
	const char	*s = "Salut boss";
	size_t		n = 5;

	ft_memmove(d, s, n);
	printf("%s \n", d);
	return (0);
}*/
