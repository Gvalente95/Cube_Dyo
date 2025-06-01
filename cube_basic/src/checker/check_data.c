/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:15:00 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 08:08:36 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	*ft_strstr(char *str, char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*to_find)
		return (str);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		while (to_find[j] && str[i + j]
			&& i + j < len && str[i + j] == to_find[j])
		{
			if (!to_find[j])
				return (&str[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

static char	*ft_strrstr(char *str, char *to_find, size_t len)
{
	size_t	i;

	if (!*to_find)
		return (str + len);
	i = len;
	while (i > 0)
	{
		if (i >= ft_strlen(to_find) && !ft_strncmp(&str[i - ft_strlen(to_find)], to_find, ft_strlen(to_find)))
			return (&str[i - ft_strlen(to_find)]);
		i--;
	}
	return (NULL);
}

static bool	is_in_file(char *doc, int tok, char *tokens[NO_TOKEN])
{
	char	*is_token;
	int		i;

	i = 0;
	is_token = ft_strnstr(doc, tokens[tok], ft_strlen(doc));
	if (is_token)
	{
		is_token += ft_strlen(tokens[tok]);
		while (is_token[i] && ft_isspace(is_token[i]))
			if (is_token[i++] == '\n')
				break ;
		if (no_char_in_line(is_token, (int)ft_strlen(tokens[tok]), i))
			return (false);
		return (true);
	}
	return (false);
}

static bool	is_in_double(char *doc, int tok, char *tokens[NO_TOKEN])
{
	char	*first_occurence;
	char	*last_occurence;

	first_occurence = ft_strstr(doc, tokens[tok], ft_strlen(tokens[tok]));
	last_occurence = ft_strrstr(doc, tokens[tok], ft_strlen(tokens[tok]));
	if (first_occurence && last_occurence && first_occurence != last_occurence)
		return (true);
	return (false);
}

#define NO_ERROR 0
#define ERROR 1

static bool	print_error_messages(t_data *data, bool list[NO_TOKEN])
{
	int			i;
	static char	*errors[] = {"NO PATH MISSING OR INCOMPLETE",
		"SO PATH MISSING OR INCOMLPETE", "EA PATH MISSING OR INCOMPLETE",
		"WE PATH MISSING OR INCOMPLETE", "FLOOR COLOR MISSING OR INCOMPLETE",
		"SKY COLOR MISSING OR INCOMPLETE", "WALL COLOR MISSING OR INCOMPLETE"
		};
	
	i = -1;
	data->error = malloc((1 + NO_TOKEN) * sizeof(char *));
	data->error[NO_TOKEN] = NULL;
	while (++i < NO_TOKEN)
	{
		if (list[i])
			data->error[i] = ft_strdup(errors[i]);
		else
			data->error[i] = ft_strdup("OK");
	}
	while (--i > 0)
		if (!ft_strncmp(data->error[i], "OK", ft_strlen(data->error[i])))
			return (ERROR);
	return (NO_ERROR);
}

static bool	check_tokens(t_data *data)
{
	static char	*tokens[] = {"NO", "SO", "EA", "WE", "F", "W", "C"};
	int			i;

	i = 0;
	while (i < NO_TOKEN)
	{
		if (is_in_file(data->file, i, tokens)
				&& is_in_double(data->file, i, tokens))
			data->check_list[i] = false;
		i++;
	}
	return (OK);
}

void	check_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < NO_TOKEN)
		data->check_list[i++] = OK;
	if (check_tokens(data) == KO)
		perror("Error with config file content\n");
	if (check_map(data) == KO)
		perror("Error parsing the map\n");
	free(data->file);
	data->file = NULL;
	if (print_error_messages(data, data->check_list) == NO_ERROR)
		return (string_array_free(&data->error));
	i = 0;
	while (data->error[i])
	{
		perror(data->error[i]);
		free(data->error[i++]);
	}
	free(data->error);	
	free_data(data);
	exit(EXIT_FAILURE);
}
