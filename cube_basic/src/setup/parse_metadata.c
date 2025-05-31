/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:19:54 by dyodlm            #+#    #+#             */
/*   Updated: 2025/05/31 08:12:42 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_suppress(char **content, char *to_suppress)
{
	int		i;
	char	**split;
	char	*join;

	i = 2;
	if (!content || !*content)
		return ;
	split = ft_strsplit(*content, to_suppress);
	if (!split)
		return ;
	join = ft_strjoin(split[0], split[1]);
	while (split[i])
		join = ft_strjoin(join, split[i++]);
	free(*content);
	*content = join;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
/*static void	ft_suppress(char **content, char *to_suppress)
{
	int		i = 2;
	char	**split;
	char	*join;

	if (!content || !*content || !to_suppress || !*to_suppress)
		return ;
	split = ft_strsplit(*content, to_suppress);
	if (!split)
		return ;
	join = ft_strdup(split[0]);
	while (split[i])
	{
		char *tmp = ft_strjoin(join, split[i]);
		free(join);
		join = tmp;
		i++;
	}
	free(*content);
	*content = join;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}*/

static void	get_color(t_color *object, char *line, int token)
{
	char	**color;

	printf("getting color\n");
	if (!line)
		return ;
	color = ft_split(line, ',');
	if (!color)
		return (free(line));
	printf("Line : %s\n", line);
	printf("color R : %s\n", color[0]);
	object->R = ft_atoi(color[0]);
	printf("color G : %s\n", color[1]);
	object->G = ft_atoi(color[1]);
	printf("color B : %s\n", color[2]);
	object->B = ft_atoi(color[2]);
	return (free(color[0]), free(color[1]),
		free(color[2]), free(color));
	(void)token;
}

static void	get_texture_path(char **path, char *line, int token)
{
	printf("duping path\n");
	if (!line)
		return ;
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

static char *search_token_line(char *s, const char *token)
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
            return result;
        }

        if (!next_line)
            break;
        cursor = next_line + 1;
    }
    return NULL;
}

static char	*search_token(char *s, int token)
{

	if (token == NORTH_TEXT)
		return (search_token_line(s, "NO"));
	else if (token == SOUTH_TEXT)
		return (search_token_line(s, "SO"));
	else if (token == EAST_TEXT)
		return (search_token_line(s, "EA"));
	else if (token == WEST_TEXT)
		return (search_token_line(s, "KAKA"));
	else if (token == FLOOR_COLOR)
		return (search_token_line(s, "W"));
	else if (token == SKY_COLOR)
		return (search_token_line(s, "F"));
	else if (token == WALL_COLOR)
		return (search_token_line(s, "C"));
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

	i = 0;
	while (i < NO_TOKEN)
	{
		content = search_token(*doc, i);
		line = trim_content(content);
		geters(data, line, i++);
		ft_suppress(doc, line);
		free(line);
		line = NULL;
	}
}
