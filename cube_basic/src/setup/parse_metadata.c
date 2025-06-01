/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:19:54 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 15:26:42 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	get_color(t_color *object, int *res, char *line, int token)
{
	char	**color;

	printf("getting color\n");
	if (!line)
		return ;
	color = ft_split(line, ',');
	if (!color)
		return (free(line));
	object->r = ft_atohx(color[0]);
	object->g = ft_atohx(color[1]);
	object->b = ft_atohx(color[2]);
	*res = object->r;// + object->g + object->b;
	return (free(color[0]), free(color[1]),
		free(color[2]), free(color));
	(void)token;
}

static void	geters(t_data *data, char *line, int token)
{
	if (token <= WEST_TEXT)
	{
		if (!line)
			return ;
		data->tokens.text_path[token] = ft_strdup(line);
	}
	else
		get_color(
			&data->tokens.color_objects[token - (NUM_TEXTURES + 1)],
			&data->tokens.color[token - (NUM_TEXTURES + 1)],
			line,
			token);
}

static char	*search_token_line(char *s, const char *token)
{
	char	*cursor;
	char	*next_line;
	size_t	token_len;
	char	*result;	

	cursor = s;
	token_len = ft_strlen(token);
	while (cursor && *cursor)
	{
		next_line = ft_strchr(cursor, '\n');
		if (ft_strncmp(cursor, token, token_len) == 0
			&& ft_isspace(cursor[token_len]))
		{
			result = cursor + token_len;
			while (*result && ft_isspace(*result))
				result++;
			return (result);
		}
		if (!next_line)
			break ;
		cursor = next_line + 1;
	}
	return (NULL);
}

char	*trim_content(char *content)
{
	char	*line;
	int		j;

	j = 0;
	line = NULL;
	while (content && content[j] && content[j] != '\n')
		j++;
	line = malloc(j + 1);
	if (!line)
		return (NULL);
	line[j] = '\0';
	j = 0;
	while (content && content[j] && content[j] != '\n')
	{
		line[j] = content[j];
		j++;
	}
	return (line);
}

void	parse_metadata(t_data *data, char **doc)
{
	int			i;
	char		*line;
	char		*content;
	static char	*tokens[] = {"NO", "SO", "EA", "KAKA", "W", "F", "C", NULL};

	i = 0;
	while (i < NO_TOKEN)
	{
		content = search_token_line(*doc, tokens[i]);
		line = trim_content(content);
		geters(data, line, i);
		ft_suppress(doc, line);
		free(line);
		line = NULL;
		i++;
	}
}
