/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 19:14:35 by mhonchar          #+#    #+#             */
/*   Updated: 2018/10/28 19:19:41 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sub;
	size_t	i;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(sub = (char *)malloc(len1 + len2 + 1)))
		return (NULL);
	i = 0;
	while (i < len1)
	{
		sub[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		sub[i + len1] = s2[i];
		i++;
	}
	sub[len1 + len2] = '\0';
	return (sub);
}
