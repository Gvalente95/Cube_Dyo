/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:33:45 by aseite            #+#    #+#             */
/*   Updated: 2024/10/10 19:33:46 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s[i] == 0)
		return (0);
	while (s[i])
		i++;
	return (i);
}
/*#include <stdio.h>
int	main()
{
	const char	*s = "1234";
	size_t		len;

	len = ft_strlen(s);
	printf("%zu \n", len);
	return (0);
}*/
