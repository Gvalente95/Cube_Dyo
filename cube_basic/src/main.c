/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvalente <gvalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 07:48:31 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 17:40:47 by gvalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
	ft_memset(&data, 0, sizeof(t_data));
	gather_data(&data, ac, av);
	check_data(&data);
	init_struct(&data);
	set_up_loops(&data);
	mlx_loop(data.mlx);
	return (0);
}
