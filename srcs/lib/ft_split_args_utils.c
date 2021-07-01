/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:05:05 by user42            #+#    #+#             */
/*   Updated: 2021/07/02 01:08:29 by user42           ###   ########.fr       */
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

char	**free_words(int word, char **tabword)
{
	int	i;

	i = 0;
	while (i < word)
	{
		free(tabword[i]);
		i++;
	}
	free(tabword);
	return (NULL);
}

const char	*pass_quotes(const char *str, int *inquote)
{
	str++;
	while (*str)
	{
		*inquote = check_inquote2(*str, *inquote);
		if (*inquote == 0)
		{
			str++;
			break ;
		}
		str++;
	}
	*inquote = 0;
	return (str);
}

int		count_words(const char *str, char c)
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
		{
			str = pass_quotes(str, &inquote);
			count_words++;
		}
		if (*str == c)
			ter = 0;
		else if (ter == 0 && *str != c)
		{
			ter = 1;
			count_words++;
		}
		str++;
	}
	return (count_words);
}

int	ft_word_len(const char *s, char c)
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

const char	*fill_quoted_word(const char *s, char *tab, int *inquote)
{
	int i;

	i = 0;
	while (*s)
	{
		tab[i] = *s;
		*inquote = check_inquote2(*s, *inquote);
		if (*inquote == 0)
		{
			s++;
			break ;
		}
		i++;
		s++;
	}
	tab[i] = '\0';
	return (s);
}