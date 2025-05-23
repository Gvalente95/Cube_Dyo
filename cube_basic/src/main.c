/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 07:48:31 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/07 12:13:59 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	ft_isempty(char *s)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (s && *s)
	{
		if (((*s <= 13 && *s >= 9) || *s == 32))
			s++;
		else
			break ;
		i++;
	}
	return ((i == len));
}

static char	*ajust_size(char *s1, char *s2)
{
	size_t	size;
	char	*newstr;

	if (!s1 && !s2)
		return (ft_strdup(""));
	else if (!s1 && s2)
		return (ft_strdup(s2));
	else if (s1 && !s2)
		return (s1);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = malloc(size);
	ft_strlcpy(newstr, s1, size);
	ft_strlcat(newstr, s2, size);
	return (newstr);
}

static char	*get_content(char *file)
{
	int		fd;
	ssize_t	bread;
	char	buffer[BSIZE + 1];
	char	*content;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (1)
	{
		ft_memset(&content, 0, BSIZE);
		bread = read(fd, buffer, BSIZE);
		buffer[bread] = '\0';
		content = ajust_size(content, buffer);
		if (bread < 0)
			return (free(content), NULL);
		else if (bread == 0 || bread != BSIZE)
			return (content);
	}
	return (content);
}

static void	gather_data(t_data *data, int ac, char **av)
{
	char	*doc;

	if (ac != 2 || ft_isempty(av[1]))
	{
		printf("Executer ./cub3d [map.cub]\n");
		exit(1);
	}
	init_struct(data);
	doc = get_content(av[1]);
	if (!doc)
	{
		printf("File not found\n");
		exit(1);
	}
	data->run.map = parse_map(doc);
	if (!check_map(data->run.map))
		exit_game(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	gather_data(&data, ac, av);
	set_up_loops(&data);
	mlx_loop(data.mlx);
	return (0);
}
