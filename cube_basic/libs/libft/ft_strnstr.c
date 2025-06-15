/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:34:19 by aseite            #+#    #+#             */
/*   Updated: 2025/06/01 04:17:30 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!big && !len)
		return (NULL);
	if (little[i] == 0 || little == big)
		return ((char *)big);
	while (big[i])
	{
		j = 0;
		while (big[i + j] - little[j] == 0 && (i + j) < len)
		{
			if (big[i + j] == 0 && little[j] == 0)
				return ((char *)(&big[i]));
			j++;
		}
		if (little[j] == 0)
			return ((char *)&big[i]);
		else
			i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main()
{
	const char	*big = "lorem ipsum dolor sit amet";
	const char	*little = "dolor";
	size_t		len = 18;

	printf("%s \n", ft_strnstr(big, little, len));
	return (0);
}*/
