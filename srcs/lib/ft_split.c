/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:48:11 by user42            #+#    #+#             */
/*   Updated: 2021/07/08 16:49:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		countword(const char *s, char c)
{
	int		i;
	int		nbword;

	i = 0;
	nbword = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
		{
			if (s[i + 1] == c || s[i + 1] == '\0')
				nbword++;
			i++;
		}
	}
	return (nbword);
}

static char		*sepword(const char *s, char c, int *ptr)
{
	int		j;
	int		len;
	char	*sepstr;

	len = 0;
	while (s[*ptr] == c && s[*ptr])
		*ptr = *ptr + 1;
	while (s[*ptr + len] != c && s[*ptr + len])
		len++;
	sepstr = malloc(sizeof(char) * (len + 1));
	if (sepstr == NULL)
		return (NULL);
	j = 0;
	while (j < len)
	{
		sepstr[j] = s[*ptr];
		j++;
		*ptr = *ptr + 1;
	}
	sepstr[j] = '\0';
	return (sepstr);
}

char			**ft_split(const char *s, char c)
{
	int		i;
	int		ptr;
	int		nbword;
	char	**split;

	nbword = countword(s, c);
	i = 0;
	split = malloc(sizeof(char *) * (nbword + 1));
	if (split == NULL)
		return (NULL);
	ptr = 0;
	while (i < nbword)
	{
		split[i] = sepword(s, c, &ptr);
		i++;
	}
	split[i] = NULL;
	return (split);
}