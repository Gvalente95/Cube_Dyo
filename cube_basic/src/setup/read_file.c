/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:22:36 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 08:56:05 by dyodlm           ###   ########.fr       */
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

static void	extract_map(char **doc)
{
	int		i;
	char	*map;

	i = 0;
	if (!doc || !*doc)
		return ;
	while ((*doc)[i] && (ft_isalpha((*doc)[i]) || ft_isspace((*doc)[i])))
		i++;
	while ((*doc)[i] != '\n')
		i--;
	map = copy_from(doc, i);
	printf("COPY WENT WELL\n");
	free(*doc);
	*doc = map;
}

void	gather_data(t_data *data, int ac, char **av)
{
	char	*doc;

	if (ac != 2 || ft_isempty(av[1])
		|| !ft_strnstr(av[1], ".cub", ft_strlen(av[1])))
	{
		printf("Argument Error : Executer ./cub3d [map.cub]\n");
		exit(1);
	}
	doc = get_content(av[1]);
	data->file = ft_strdup(doc);
	if (!doc)
	{
		printf("File Error : File not found\n");
		exit(1);
	}
	parse_metadata(data, &doc);
	extract_map(&doc);
	data->run.map.map = parse_map(doc);
	data->run.map.imap = scale_map(data->run.map.map, data);
	adjust_off_bounds(&data->run.map.imap, data->run.map.max);
	data->run.map.map_s
		= data->run.map.max.x * data->run.map.max.y / 10;
}
