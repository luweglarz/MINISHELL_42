/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 22:31:04 by user42            #+#    #+#             */
/*   Updated: 2021/07/05 17:06:17 by user42           ###   ########.fr       */
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

static char	**ft_cut_words(const char *s, char **tab, int nb_words)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i++ < nb_words)
	{
		while (*s == ' ')
			s++;
		tab[j] = malloc(sizeof(char) * (word_len(s) + 1));
		if (tab[j] == NULL)
		{
			ft_free_words(nb_words, tab);
			return (NULL);
		}
		s = fill_split(s, &tab[j]);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**split_args(char const *s)
{
	char	**tab;
	int		nb_words;

	nb_words = count_word(s);
	printf("count words %d\n", nb_words);
	tab = malloc(sizeof(char *) * (nb_words + 1));
	if (tab == NULL)
		return (NULL);
	return (ft_cut_words(s, tab, nb_words));
}
