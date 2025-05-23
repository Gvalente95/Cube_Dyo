/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:27:16 by aseite            #+#    #+#             */
/*   Updated: 2024/10/10 19:50:32 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}
/*
int	main()
{
	size_t		n = 20;
	const char	*s = "iiiiiiiiiiiiiiiiiiiic";
	int		c = 'c';
	char		*result;

	result = ft_memchr(s, c, n);
	if (result != NULL)
		printf("Found character at position: %ld\n", result - s);
	else
		printf("%s \n", "Not found");
	return (0);
}*/
