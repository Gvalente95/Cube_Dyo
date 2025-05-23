/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuliovalente <giuliovalente@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:09:46 by giuliovalen       #+#    #+#             */
/*   Updated: 2025/03/09 12:25:35 by giuliovalen      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lists.h"

int	dblst_size(t_dblst *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

t_dblst	*dblst_first(t_dblst *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

t_dblst	*dblst_last(t_dblst *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_dblst	*get_dblst_at_key(t_dblst *lst, char *key)
{
	t_dblst	*start;
	char		*str;
	int			j;

	if (!lst || !key)
		return (NULL);
	lst = dblst_first(lst);
	start = lst;
	while (lst)
	{
		str = (char *)lst->content;
		if (str)
		{
			j = 0;
			while (key[j] && str[j] && str[j] == key[j])
				j++;
			if ((str[j] == '=' && key[j] == '\0') || (!key[j] && !str[j]))
				return (lst);
		}
		lst = lst->next;
		if (lst == start)
			break ;
	}
	return (NULL);
}
