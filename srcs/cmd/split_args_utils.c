/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:05:05 by user42            #+#    #+#             */
/*   Updated: 2021/07/29 19:25:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_end_quote(const char *s)
{
	int	i;
	int	c;

	i = 0;
	c = *s;
	s++;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static const char
	*check_inquote_split(const char *s, int *inquote)
{
	if ((*s == '\'' && *inquote == 0) || (*s == '"' && *inquote == 0))
	{
		if (check_end_quote(s) == 1)
		{
			if (*s == '\'')
				*inquote = 1;
			else if (*s == '"')
				*inquote = 2;
			return (s);
		}
	}
	else if ((*s == '\'' && *inquote == 1) || (*s == '"' && *inquote == 2))
	{
		*inquote = 0;
		return (s);
	}
	return (s);
}

int	count_word(const char *str)
{
	int	count_words;
	int	ter;
	int	inquote;

	count_words = 0;
	ter = 0;
	inquote = 0;
	while (*str)
	{
		str = check_inquote_split(str, &inquote);
		if (*str == '|' && inquote == 0)
			break;
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
	int	inquote;

	size = 0;
	inquote = 0;
	while (*s)
	{
		if ((*s == ' ' && inquote == 0) || (*s == '|' && inquote == 0))
			break ;
		s = check_inquote_split(s, &inquote);
		s++;
		size++;
	}
	return (size);
}

const char	*fill_split(const char *s, char **tab)
{
	int		inquote;
	int		k;

	inquote = 0;
	k = 0;
	while (*s)
	{
		if ((*s == ' ' && inquote == 0) || (*s == '|' && inquote == 0))
			break ;
		s = check_inquote_split(s, &inquote);
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
