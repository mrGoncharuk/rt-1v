/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 21:01:58 by mhonchar          #+#    #+#             */
/*   Updated: 2018/10/27 20:45:39 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*uc_src;
	unsigned char		*uc_dest;

	uc_src = src;
	uc_dest = dest;
	if (uc_dest < uc_src)
	{
		i = 0;
		while (i < n)
		{
			uc_dest[i] = uc_src[i];
			i++;
		}
	}
	else if (uc_dest > uc_src)
	{
		i = n;
		while (i > 0)
		{
			uc_dest[i - 1] = uc_src[i - 1];
			i--;
		}
	}
	return (dest);
}
