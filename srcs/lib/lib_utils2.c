/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 21:38:29 by user42            #+#    #+#             */
/*   Updated: 2021/07/01 11:55:51 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i + 1);
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		return ((char *)s + i);
	return (NULL);
}

int	ft_strclen(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	if (str[i] == (char)c)
		return (i);
	return (-1);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len;
	char	*join;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * (len + 1));
	if (join == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}
