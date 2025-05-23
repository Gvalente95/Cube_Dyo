/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:25:44 by aseite            #+#    #+#             */
/*   Updated: 2024/10/10 19:45:45 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
//#include <stdio.h>

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n-- != 0)
		*p++ = (unsigned char)c;
	return (s);
}

void	*ft_calloc(size_t num, size_t size)
{
	size_t	ns;
	void	*news;

	ns = num * size;
	news = malloc(ns);
	if (!news)
		return (NULL);
	ft_memset(news, 0, ns);
	return (news);
}
/*
int	main()
{
	int	*s;
	int	i;
	int	n = 5;

	i = 0;
	s = (int*)ft_calloc(n, sizeof(int));
	if (s == NULL)
	{
		printf("Fuck \n");
		return (1);
	}
	while (i < n)
		printf("%d ", s[i++]);
	free(s);
	return (0);
}*/
