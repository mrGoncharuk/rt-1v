/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 17:12:18 by mhonchar          #+#    #+#             */
/*   Updated: 2018/10/27 17:12:30 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char *ptr;

	ptr = (const char *)s;
	while (n > 0)
	{
		if (*ptr == (char)c)
			return ((void *)ptr);
		n--;
		ptr++;
	}
	return (NULL);
}
