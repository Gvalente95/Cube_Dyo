/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:29:04 by aseite            #+#    #+#             */
/*   Updated: 2024/10/10 19:29:07 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
//#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n-- != 0)
		*p++ = (unsigned char)c;
	return (s);
}
/*
int	main()
{
	char	buffer[20] = "Hello, World!";

	printf("Avant memset : %s\n", buffer);
	ft_memset(buffer, '-', 5);
	printf("Après memset : %s\n", buffer);
	
	return (0);
}*/
