/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aseite <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:50:44 by aseite            #+#    #+#             */
/*   Updated: 2024/10/18 10:57:10 by aseite           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
int	main()
{
	t_list	*list = NULL;
	t_list	*new = "banana"2;
	t_list	*new_node;
	
	new_node = malloc(sizeof(t_list));
	printf("%s \n", new);
	new_node->content = "Hello";
	printf("%s \n", content);
	new_node->next = NULL;
	
	ft_lstadd_front(&list, new_node);
	printf("%s \n", content);
	return (0);
}*/
