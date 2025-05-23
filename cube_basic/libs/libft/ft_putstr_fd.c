/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:30:13 by aseite            #+#    #+#             */
/*   Updated: 2024/10/10 19:30:17 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}
/*
int	main()
{
	char	*s = "www";

	write(1, "\n", 1);
	ft_putstr_fd(s, 1);
	write(1, "\n", 1);
	return (0);
}*/
