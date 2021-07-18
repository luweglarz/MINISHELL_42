/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 20:52:08 by user42            #+#    #+#             */
/*   Updated: 2021/07/18 04:40:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_inquote(int c, int inquote)
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

int	check_solo_quote(char *arg, int inquote)
{
	int	i;

	i = 0;
	if (arg[i] == '\'' && inquote == 1)
		return (check_quote(arg, i, '\''));
	else if (arg[i] == '"' && inquote == 2)
		return (check_quote(arg, i, '"'));
	else
		return (inquote);
}

int	check_quote(char *arg, int i, char c)
{
	int	ret;

	if (c == '\'')
		ret = 1;
	else if (c == '"')
		ret = 2;
	i++;
	while (arg[i])
	{
		if (arg[i] == c)
			return (ret);
		i++;
	}
	if (arg[i] == c)
		return (ret);
	return (0);
}

int	check_space_unused(const char *line, int i, int redirection)
{
	i++;
	if (redirection == 1 && (line[i] == '>' || line[i] == '<'))
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	check_unused(const char *line)
{
	int	i;
	int	inquote;

	i = 0;
	inquote = 0;
	while (line[i])
	{
		inquote = check_inquote(line[i], inquote);
		if ((line[i] == '>' || line[i] == '<') && inquote == 0)
		{
			i = check_space_unused(line, i, 1);
			if (line[i] == '\0' || line[i] == '|')
				return (-1);
		}
		if (line[i] == '|' && inquote == 0)
		{
			i = check_space_unused(line, i, 0);
			if (line[i] == '\0' || line[i] == '|')
				return (-1);
		}
		i++;
	}
	return (1);
}
