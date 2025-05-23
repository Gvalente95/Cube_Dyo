/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:27:48 by aseite            #+#    #+#             */
/*   Updated: 2024/10/10 19:57:42 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
//#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*st1;
	unsigned char	*st2;

	if (n == 0)
		return (0);
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	while ((*st1 == *st2) && n - 1 > 0)
	{
		st1++;
		st2++;
		n--;
	}
	return ((int)(*st1 - *st2));
}
/*
int	main()
{
	size_t		n = 6;
	unsigned char	*s1 = "abcdefg";
	char unsigned	*s2 = "asssss";
	int		d;

	d = ft_memcmp(s1, s2, n);
	printf("%d \n", d);
	return (0);
}*/
