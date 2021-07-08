/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:05:05 by user42            #+#    #+#             */
/*   Updated: 2021/07/08 17:19:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_end_quote(const char *s)
{
	int	i;

	i = 0;
	s++;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

static const char
	*check_inquote_split(const char *s, int *inquote, int *docontinue)
{
	if ((*s == '\'') ||(*s == '"' && *inquote == 0))
	{
		if (check_end_quote(s) == 1)
		{
			*inquote = 1;
			s++;
			*docontinue = 1;
			return (s);
		}
	}
	else if ((*s == '\'') || (*s == '"' && *inquote == 1))
	{
		*inquote = 0;
		s++;
		*docontinue = 1;
		return (s);
	}
	return (s);
}

int	count_word(const char *str)
{
	int	count_words;
	int	ter;
	int	docontinue;
	int	inquote;

	count_words = 0;
	ter = 0;
	inquote = 0;
	while (*str)
	{
		docontinue = 0;
		str = check_inquote_split(str, &inquote, &docontinue);
		if (docontinue == 1)
			continue ;
		if (*str == ' ' && inquote == 0)
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

int	word_len(const char *s)
{
	int	size;
	int	docontinue;
	int	inquote;

	size = 0;
	while (*s)
	{
		docontinue = 0;
		if (*s == ' ' && inquote == 0)
			break ;
		s = check_inquote_split(s, &inquote, &docontinue);
		if (docontinue == 1)
			continue ;
		s++;
		size++;
	}
	return (size);
}

const char	*fill_split(const char *s, char **tab)
{
	int		inquote;
	int		docontinue;
	int		k;

	inquote = 0;
	k = 0;
	while (*s)
	{
		docontinue = 0;
		if (*s == ' ' && inquote == 0)
			break ;
		s = check_inquote_split(s, &inquote, &docontinue);
		if (docontinue == 1)
			continue ;
		if (inquote == 1 && *s == ' ')
		{
			(*tab)[k++] = *s++;
			continue ;
		}
		(*tab)[k++] = *s++;
	}
	(*tab)[k] = '\0';
	return (s);
}
