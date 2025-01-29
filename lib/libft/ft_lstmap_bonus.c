/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:10:01 by antonimo          #+#    #+#             */
/*   Updated: 2024/04/30 13:31:39 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_element;

	if (lst == NULL)
		return (NULL);
	new_list = NULL;
	while (lst != NULL)
	{
		new_element = ft_lstnew(NULL);
		if (new_element == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_element->content = f(lst->content);
		ft_lstadd_back(&new_list, new_element);
		lst = lst->next;
	}
	return (new_list);
}
