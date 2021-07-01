/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 22:31:04 by user42            #+#    #+#             */
/*   Updated: 2021/07/01 15:04:42 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_inquote2(int c, int inquote)
{
	if (c == '\'' && inquote == 0)
		return (1);
	else if (c == '"' && inquote == 0)
		return (2);
	else if (c == '\'' && inquote == 1)
		return (0);
	else if (c == '"' && inquote == 2)
		return (0);
	else 
		return (inquote);
}

static	void		ft_free_words(int word, char **tabword)
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

const char	*in_quotes(const char *str, int inquote)
{
	str++;
	while (*str)
	{
		inquote = check_inquote2(*str, inquote);
		if (inquote == 0)
			break ;
		str++;
	}
	return (str);
}

static	int			ft_is_word(const char *str, char c)
{
	int		count_words;
	int		ter;
	int		inquote;

	count_words = 0;
	ter = 0;
	inquote = 0;
	while (*str)
	{	
		inquote = check_inquote2(*str, inquote);
		if (inquote == 1 || inquote == 2)
			str = in_quotes(str, inquote);
		inquote = 0;
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

static	int			ft_word_len(const char *s, char c)
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

static char			**ft_cut_words(const char *s, char c, char **tab, int words)
{
	int		i;
	int		j;
	int		k;
	int		inquote;

	i = 0;
	j = 0;
	inquote = 0;
	while (i++ < words)
	{
		while (*s == c)
			s++;
		inquote = check_inquote2(*s, inquote);
		if (inquote == 1 || inquote == 2)
		{
			k = 0;
			printf("la\n");
			s++;
			while (*s)
			{
				printf("s c |%c|\n", *s);
				printf("j %d\n k %d\n", j, k);
				tab[j][k++] = *s;
				inquote = check_inquote2(*s, inquote);
				if (inquote == 0)
				{
					s++;
					break ;
				}
				s++;
			}
			j++;
		}
		inquote = 0;
		while (*s == c)
			s++;
		if (!(tab[j] = malloc(sizeof(char) * (ft_word_len(s, c) + 1))))
		{
			ft_free_words(words, tab);
			return (NULL);
		}
		k = 0;
		printf("j = %d\n", j);
		if (j >= words)
				return (tab);
				printf("le s %s\n", s);
		while (*s && *s != c)
			tab[j][k++] = *s++;
		printf("test2\n");
		tab[j][k] = '\0';
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

char				**ft_split(char const *s, char c)
{
	char	**tab;
	int		count_words;

	count_words = ft_is_word(s, c);
	printf("count woord %d\n", count_words);
	if (!(tab = malloc(sizeof(char *) * (count_words + 1))))
		return (NULL);
	return (ft_cut_words(s, c, tab, count_words));
}