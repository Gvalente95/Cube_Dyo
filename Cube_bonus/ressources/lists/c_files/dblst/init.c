/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:07:37 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/03/09 12:25:35 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lists.h"

t_dblst	*dblst_new(void *content)
{
	t_dblst	*new;

	new = malloc(sizeof(t_dblst));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	dblst_add_back(t_dblst **lst, t_dblst *new)
{
	t_dblst	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		new->next = NULL;
		new->prev = NULL;
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
	new->next = NULL;
}

void	dblst_add_front(t_dblst **lst, t_dblst *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	new->prev = NULL;
	(*lst)->prev = new;
	*lst = new;
}

t_dblst	*arr_to_dblst(void **values)
{
	t_dblst	*lst;
	t_dblst	*new_node;
	int			i;

	if (!values)
		return (NULL);
	lst = NULL;
	i = 0;
	while (values[i])
	{
		new_node = dblst_new(list_strdup(values[i]));
		if (!new_node)
			return (dblst_clear(&lst, free), NULL);
		dblst_add_back(&lst, new_node);
		i++;
	}
	return (lst);
}
