/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_slash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:26:40 by user42            #+#    #+#             */
/*   Updated: 2021/07/18 05:02:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	ft_free_words(int word, char **tabword)
{
	int	i;

	i = 0;
	while (i < word)
	{
		free(tabword[i]);
		i++;
	}
	free(tabword);
}

static	int	ft_is_word(const char *str, char c)
{
	int		count_words;
	int		ter;

	count_words = 0;
	ter = 0;
	while (*str)
	{
		if (*str == c)
			ter = 0;
		else if (ter == 0)
		{
			ter = 1;
			count_words++;
		}
		str++;
	}
	return (count_words);
}

static	int	ft_word_len(const char *s, char c)
{
	int	size;

	size = 0;
	while (*s != c && *s != '\0')
	{
		s++;
		size++;
	}
	return (size);
}

static char	**ft_cut_words(const char *s, char c, char **tab, int words)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (i++ < words)
	{
		while (*s == c)
			s++;
		if (!(tab[j] = malloc(sizeof(char) * (ft_word_len(s, c) + 1 + 1))))
		{
			ft_free_words(words, tab);
			return (NULL);
		}
		k = 0;
		while (*s && *s != c)
			tab[j][k++] = *s++;
		tab[j][k++] = '/';
		tab[j][k] = '\0';
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split_slash(char const *s, char c)
{
	char	**tab;
	int		count_words;

	count_words = ft_is_word(s, c);
	if (!(tab = malloc(sizeof(char *) * (count_words + 1))))
		return (NULL);
	return (ft_cut_words(s, c, tab, count_words));
}
