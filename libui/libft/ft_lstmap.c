/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:19:54 by mhonchar          #+#    #+#             */
/*   Updated: 2018/11/01 20:19:56 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*node;
	t_list	*head;

	if (!lst || !f)
		return (NULL);
	if (!(node = f(lst)))
		return (NULL);
	head = node;
	while (lst->next)
	{
		lst = lst->next;
		if (!(node->next = f(lst)))
			return (NULL);
		node = node->next;
	}
	return (head);
}
