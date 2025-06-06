/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:13 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/03/09 12:25:35 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lists.h"

static t_dblst	*get_db_list(t_dblst *lst, void *(*f)(void *), \
	void (*del)(void *))
{
	t_dblst	*new_node;
	t_dblst	*new_list;
	void		*new_content;

	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		if (!new_content)
		{
			dblst_clear(&new_list, del);
			return (NULL);
		}
		new_node = dblst_new(new_content);
		if (!new_node)
		{
			del(new_content);
			dblst_clear(&new_list, del);
			return (NULL);
		}
		dblst_add_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

t_dblst	*dblst_map(t_dblst *lst, void *(*f)(void *), \
	void (*del)(void *))
{
	if (!lst || !f)
		return (NULL);
	return (get_db_list(lst, f, del));
}

void	dblst_iter(t_dblst *lst, void (*f)(void *))
{
	t_dblst	*start;

	if (!lst || !f)
		return ;
	lst = dblst_first(lst);
	if (!lst)
		return ;
	start = lst;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
		if (lst == start)
			break ;
	}
}
