/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:19:54 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/30 11:58:12 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	ft_suppress(char **str, char *to_suppress)
{
	(void)str;
	(void)to_suppress;
}

static void	get_color(t_color *object, char *line, int token)
{
	char	**color;

	color = ft_split(line, ',');
	if (!color)
		return ;
	object->R = ft_atoi(color[0]);
	object->G = ft_atoi(color[1]);
	object->B = ft_atoi(color[2]);
	return (free(color[0]), free(color[1]),
		free(color[2]), free(color));
	(void)token;
}

static void	get_texture_path(char **path, char *line, int token)
{
	*path = ft_strdup(line);
	(void)token;
}

static void	geters(t_data *data, char *line, int token)
{
	if (token <= WEST_TEXT)
		get_texture_path(&data->tokens.text_path[token],
			line,
			token);
	else
		get_color(
			&data->tokens.color_objects[token - (NUM_TEXTURES + 1)],
			line,
			token);
}

static int	ft_isspace(int c)
{
	return ((c <= 13 && c >= 9) || c == 32);
}

static char	*search_token(char *s, int token)
{
	char	*line;

	if (token == NORTH_TEXT)
		line = ft_strnstr(s, "NO", sizeof(s));
	else if (token == SOUTH_TEXT)
		line = ft_strnstr(s, "SO", sizeof(s));
	else if (token == EAST_TEXT)
		line = ft_strnstr(s, "EA", sizeof(s));
	else if (token == WEST_TEXT)
		line = ft_strnstr(s, "WE", sizeof(s));
	else if (token == W_COLOR)
		line = ft_strnstr(s, "W", sizeof(s));
	else if (token == F_COLOR)
		line = ft_strnstr(s, "F", sizeof(s));
	else if (token == C_COLOR)
		line = ft_strnstr(s, "C", sizeof(s));
	else
		return (NULL);
	while (*line && ft_isspace(*line))
		line++;
	return (line);
}

void	parse_metadata(t_data *data, char **doc)
{
	int			i;
	char		*line;

	i = 0;
	while (i < NO_TOKEN)
	{
		line = search_token(*doc, i);
		geters(data, line, i++);
		ft_suppress(doc, line);
	}
}
