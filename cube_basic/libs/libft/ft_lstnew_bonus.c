/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:49 by aseite            #+#    #+#             */
/*   Updated: 2024/10/18 10:51:51 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*duplicate(void *content, size_t size)
{
	void	*new;

	if (!content)
		return (NULL);
	new = malloc(size);
	if (!new)
		return (NULL);
	ft_memcpy(new, content, size);
	return (new);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;
	size_t	size;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	size = ft_lstsize(content);
	new_node->content = duplicate(content, size);
	if (!new_node->content)
		return (free(new_node), NULL);
	else
		new_node->content = NULL;
	new_node->next = NULL;
	return (new_node);
}
/*
#include <stdio.h>

int	main()
{
	int	value = 42;
	t_list *node = ft_lstnew(&value);

	if (node)
		printf("Content: %d\n", *(int *)(node->content));
	free(node);
	return (0);
}*/
