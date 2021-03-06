/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 02:17:49 by user42            #+#    #+#             */
/*   Updated: 2021/08/24 17:18:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_sep(const char *line)
{
	int	i;
	int	inquote;
	int	etat;

	i = 0;
	inquote = 0;
	etat = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\0' && line[i] != '|')
			etat = 1;
		inquote = check_inquote(line[i], inquote);
		if (line[i] == '|' && inquote == 0 && etat == 1)
		{
			while (line[i++] == ' ' && inquote == 0)
				inquote = check_inquote(line[i], inquote);
			if (line[i] == '|' || line[i] == '\0')
				return (-1);
		}
		else if (line[i] == '|' && inquote == 0 && etat == 0)
			return (-1);
		i++;
	}
	return (1);
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
		i++;
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

int	not_only_space(const char *line)
{
	int	i;
	int	others;

	i = 0;
	others = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			others++;
		i++;
	}
	if (others == 0)
		return (-1);
	else
		return (1);
}
