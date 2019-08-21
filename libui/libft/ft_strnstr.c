/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 17:22:27 by mhonchar          #+#    #+#             */
/*   Updated: 2018/11/09 18:47:13 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;

	if (*to_find == '\0')
		return ((char *)str);
	i = ft_strlen(to_find);
	while (*str != '\0' && len-- >= i)
	{
		if (*str == *to_find && ft_memcmp(str, to_find, i) == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
