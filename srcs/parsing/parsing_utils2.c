/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 02:17:49 by user42            #+#    #+#             */
/*   Updated: 2021/07/14 02:43:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_sep(const char *line)
{
	int	i;
	int	inquote;

	i = 0;
	inquote = 0;
	while (line[i])
	{
		inquote = check_inquote(line[i], inquote);
		if ((line[i] == ';' || line[i] == '|') && inquote == 0)
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == ';' || line[i] == '|')
				return (-1);
		}
		i++;
	}
	return (1);
}

int	check_unclosed(const char *line)
{
	int	i;
	int	inquote;

	i = 0;
	inquote = 0;
	while (line[i])
	{
		inquote = check_inquote(line[i], inquote);
		i++;
	}
	if (inquote == 0)
		return (1);
	else
		return (-1);
}

int	check_redirection_output(const char *line, int i)
{
	i++;
	if (line[i] == '>')
	{
		i++;
		if (line[i] == '>' || line[i] == '<')
			return (-1);
	}
	else if (line[i] == '<')
		return (-1);
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '>' || line[i] == '<')
		return (-1);
	return (i);
}

int	check_redirection_input(const char *line, int i)
{
	i++;
	if (line[i] == '<')
	{
		i++;
		if (line[i] == '>' || line[i] == '<')
			return (-1);
	}
	else if (line[i] == '>')
		return (-1);
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '>' || line[i] == '<')
		return (-1);
	return (i);
}

int	check_redirection(const char *line)
{
	int	i;
	int	inquote;

	i = 0;
	inquote = 0;
	while (line[i])
	{
		inquote = check_inquote(line[i], inquote);
		if (line[i] == '>' && inquote == 0)
		{
			i = check_redirection_output(line, i);
			if (i == -1)
				return (-1);
		}
		else if (line[i] == '<' && inquote == 0)
		{
			i = check_redirection_input(line, i);
			if (i == -1)
				return (-1);
		}
		i++;
	}
	return (1);
}
