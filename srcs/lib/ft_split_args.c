/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 22:31:04 by user42            #+#    #+#             */
/*   Updated: 2021/07/02 01:16:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const char	*cut_words_quoted(const char *s, char ***tab, int *j)
{
	int	inquote;

	inquote = 0;
	inquote = check_inquote(*s, inquote);
	if (inquote == 1 || inquote == 2)
	{
		s++;
		if (inquote == 2)
			(*tab)[*j] = malloc(sizeof(char) * ft_word_len(s, '"') + 1);
		else if (inquote == 1)
			(*tab)[*j] = malloc(sizeof(char) * ft_word_len(s, '\'') + 1);
		if ((*tab)[*j] == NULL)
			return ((*tab)[*j]);
		s = fill_quoted_word(s, (*tab)[*j], &inquote);
		*j = *j + 1;
	}
	return (s);
}

static const char	*cut_words_non_quoted(const char *s, char ***tab, int *j, int c)
{
	int	i;
	int	inquote;

	i = 0;
	inquote = 0;
	inquote = check_inquote(*s, inquote);
	if (*s != '"' || *s != '\'')
	{
		(*tab)[*j] = malloc(sizeof(char) * ft_word_len(s, c) + 1);
		if ((*tab)[*j] == NULL)
			return (*tab[*j]);
		while ((*s && *s != c) && (*s != '"' || *s != '\''))
		{
			(*tab)[*j][i] = *s;
			s++;
			i++;
		}
		(*tab)[*j][i] = '\0';
		*j = *j + 1;
	}
	return (s);
}

static char			**cut_words(const char *s, char c, char **tab, int words)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i++ < words)
	{
		while (*s == c)
			s++;
		s = cut_words_quoted(s, &tab, &j);
		if (s == NULL)
			return (free_words(words, tab));
		if (j >= words)
			return (tab);
		while (*s == c)
			s++;
		s = cut_words_non_quoted(s, &tab, &j, c);
		if (s == NULL)
			return (free_words(words, tab));
	}
	tab[j] = NULL;
	return (tab);
}

char				**ft_split_args(char const *s, char c)
{
	char	**tab;
	int		words;

	words = count_words(s, c);
	printf("nb words %d\n", words);
	if (!(tab = malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	return (cut_words(s, c, tab, words));
}
