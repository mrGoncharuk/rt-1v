/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 20:08:25 by mhonchar          #+#    #+#             */
/*   Updated: 2018/10/28 20:48:10 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_space(char s)
{
	return (s == ' ' || s == '\n' || s == '\t');
}

char		*ft_strtrim(char const *s)
{
	char	*sub;
	size_t	start;
	size_t	end;

	if (!s)
		return (NULL);
	start = 0;
	while (ft_is_space(s[start]) && s[start] != '\0')
		start++;
	if (s[start] == '\0')
	{
		if (!(sub = (char *)(malloc(1))))
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	end = ft_strlen(s);
	while (end != 0 && ft_is_space(s[end - 1]))
		end--;
	return (ft_strsub(s, start, end - start));
}
