/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 22:31:04 by user42            #+#    #+#             */
/*   Updated: 2021/09/15 23:56:01 by user42           ###   ########.fr       */
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

static char	
	**ft_cut_words(const char *s, const char *builtin, char **tab, int words)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab[j++] = ft_strdup(builtin);
	while (i++ < words)
	{
		while (*s == ' ')
			s++;
		tab[j] = malloc(sizeof(char) * (word_len(s) + 1));
		if (tab[j] == NULL)
		{
			ft_free_words(words, tab);
			return (NULL);
		}
		s = fill_split(s, &tab[j]);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**split_args(char const *s, const char *builtin)
{
	char	**tab;
	int		nb_words;

	nb_words = count_word(s);
	tab = malloc(sizeof(char *) * (nb_words + (1 + 1)));
	if (tab == NULL)
		return (NULL);
	return (ft_cut_words(s, builtin, tab, nb_words));
}
