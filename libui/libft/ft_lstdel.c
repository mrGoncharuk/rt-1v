/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:18:08 by mhonchar          #+#    #+#             */
/*   Updated: 2018/11/01 20:18:12 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*node;
	t_list	*next_node;

	if (!alst || !del)
		return ;
	node = *alst;
	while (node)
	{
		next_node = node->next;
		ft_lstdelone(&node, del);
		node = next_node;
	}
	*alst = NULL;
}
