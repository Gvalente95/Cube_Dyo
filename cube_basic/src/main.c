/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 07:48:31 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/30 12:09:39 by dyodlm           ###   ########.fr       */
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

static void	print_map(int **imap)
{
	for (int i = 0; imap && imap[i]; i++)
	{
		for (int j = 0; imap[i][j] != INT_MAX; j++)
			printf("%d ", imap[i][j]);
		printf("\n");
	}
}

/*char	*copy_from(char **s, int here)
{
	size_t	len;
	char	*copy;
	char	*new_s;

	len = ft_strlen(*s) - here;
	copy = malloc((len + 1) * sizeof(char));
	if (!copy)
		return (NULL);
	len = ft_strlen(*s) - len;
	new_s = malloc((len + 1));
	if (!new_s)
		return (free(copy), NULL);
	len = 0;
	while (*s[here])
		copy[len++] = *s[here++];
	copy[len] = '\0';
	len = -1;
	while (++len < here)
		new_s[len] = *s[len];
	new_s[len] = '\0';
	free(*s);
	*s = new_s;
	return (copy);
}*/

static void	gather_data(t_data *data, int ac, char **av)
{
	char	*doc;

	if (ac != 2 || ft_isempty(av[1]))
	{
		printf("Executer ./cub3d [map.cub]\n");
		exit(1);
	}
	doc = get_content(av[1]);
	if (!doc)
	{
		printf("File not found\n");
		exit(1);
	}
	parse_metadata(data, &doc);
	data->run.map.map = parse_map(doc);
	data->run.map.imap = scale_map(data->run.map.map, data);
	free_data(data);
	exit(1);
	print_map(data->run.map.imap);
	data->run.map.mapS = data->run.map.max.x * data->run.map.max.y / 10;
//	if (!check_map(data->run.map.map))
//		exit_game(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	gather_data(&data, ac, av);
	init_struct(&data);
	set_up_loops(&data);
	mlx_loop(data.mlx);
	return (0);
}
