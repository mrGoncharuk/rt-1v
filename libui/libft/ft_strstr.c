/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 21:23:54 by mhonchar          #+#    #+#             */
/*   Updated: 2018/10/27 19:12:20 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	finder(const char *str, const char *to_find)
{
	int i;
	int p;

	i = 0;
	p = 0;
	while (to_find[i] != '\0')
	{
		if (str[i] == to_find[i])
			p++;
		else
			return (0);
		i++;
	}
	if (p == i)
		return (1);
	else
		return (0);
}

char		*ft_strstr(const char *str, const char *to_find)
{
	if (to_find[0] == '\0')
		return ((char *)str);
	while (*str != '\0')
	{
		if (finder(str, to_find))
			return ((char*)str);
		str++;
	}
	return (0);
}
