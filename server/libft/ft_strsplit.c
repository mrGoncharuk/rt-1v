/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 22:17:28 by mhonchar          #+#    #+#             */
/*   Updated: 2018/10/31 22:17:39 by mhonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	i = 0;
	if (s[i] != c)
		words++;
	i++;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i - 1] == c)
			words++;
		i++;
	}
	return (words);
}

static size_t	ft_word_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char		**ft_free_all(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
	}
	free(tab);
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	words;
	size_t	i;
	size_t	w;

	if (!s)
		return (NULL);
	i = 0;
	w = 0;
	words = ft_count_words(s, c);
	if (!(tab = (char **)malloc(sizeof(*tab) * words + 1)))
		return (NULL);
	while (s[i] != '\0')
		if (s[i] != c)
		{
			if (!(tab[w] = ft_strsub(s, i, ft_word_len((s + i), c))))
				return (ft_free_all(&(*tab)));
			i += ft_word_len((s + i), c);
			w++;
		}
		else
			i++;
	tab[words] = NULL;
	return (tab);
}
