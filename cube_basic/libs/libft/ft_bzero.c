/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:25:34 by aseite            #+#    #+#             */
/*   Updated: 2024/10/10 19:45:16 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
//#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	z;
	unsigned char	*p;

	z = '\0';
	p = s;
	while (n > 0)
	{
		*p = z;
		p++;
		n--;
	}
}
/*
int	main()
{
	char	s[20] = "Ai-je bien compris ?";
	size_t	n = 1;

	ft_bzero(s, n);
	printf("%s\n", s);
	return (0);
}*/
