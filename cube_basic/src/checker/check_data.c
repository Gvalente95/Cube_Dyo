/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyodlm <dyodlm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:15:00 by dyodlm            #+#    #+#             */
/*   Updated: 2025/06/01 04:52:15 by dyodlm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	*ft_strstr(char *str, char *to_find, size_t len)
{
	size_t i, j;

	printf("FINDING 1\n");
	if (!*to_find)
		return (str);
	for (i = 0; str[i] && i < len; i++) {
		for (j = 0; to_find[j] && str[i + j] && i + j < len && str[i + j] == to_find[j]; j++)
			;
		if (!to_find[j])
			return (&str[i]);
	}
	return (NULL);
}

static char	*ft_strrstr(char *str, char *to_find, size_t len)
{
	size_t i;

	printf("FINDING 2\n");
	if (!*to_find)
		return (str + len);
	for (i = len; i > 0; i--) {
		if (i >= ft_strlen(to_find) && !ft_strncmp(&str[i - ft_strlen(to_find)], to_find, ft_strlen(to_find)))
			return (&str[i - ft_strlen(to_find)]);
	}
	return (NULL);
}

/*static bool	no_char_in_line(char *doc, int start, int end)
{
	while (start < end)
	{
		if (ft_isalpha(doc[start]) || ft_isalnum(doc[start]))
			return (false);
		start++;
	}
	return (true);
}*/

static bool	is_in_file(char *doc, int tok, char *tokens[NO_TOKEN])
{
	char	*is_token;
	int		i;

	i = 0;
	printf("is in file ?\n");
	is_token = ft_strnstr(doc, tokens[tok], ft_strlen(doc));
	if (is_token)
	{
		is_token += ft_strlen(tokens[tok]);
		while (is_token[i] && ft_isspace(is_token[i]))
			if (is_token[i] == '\n')
				i++;
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

	printf("Is in double ?\n");
	first_occurence = ft_strstr(doc, tokens[tok], ft_strlen(tokens[tok]));
	last_occurence = ft_strrstr(doc, tokens[tok], ft_strlen(tokens[tok]));
	if (first_occurence && last_occurence && first_occurence != last_occurence)
		return (true);
	//while (first_occurence && first_occurence[len_to_end_of_line])
	//	len_to_end_of_line++;
	//if (first_occurence && !last_occurence)
	//	return (false);
	//if (!ft_strncmp(
	//			first_occurence,
	//			last_occurence,
	//			ft_strlen(first_occurence) + len_to_end_of_line
	//			))
	//	return (true);
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
	printf("checking tokens\n");
	while (i < NO_TOKEN)
	{
		if (is_in_file(data->file, i, tokens)
				&& !is_in_double(data->file, i, tokens))
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
	//if (check_map(data) == KO)
	//	perror("Error Parsing map :\n");
	free(data->file);
	data->file = NULL;
	printf("Printing error messges\n");
	if (print_error_messages(data, data->check_list) == NO_ERROR)
		return ;
	printf("Error ther is\n");
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
