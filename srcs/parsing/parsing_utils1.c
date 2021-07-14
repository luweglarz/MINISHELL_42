/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 20:52:08 by user42            #+#    #+#             */
/*   Updated: 2021/07/14 13:39:09 by user42           ###   ########.fr       */
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

void	init_env_parse(t_pars *pars)
{
	pars->expanded = NULL;
	pars->res = NULL;
	pars->tmp = NULL;
	pars->tmp2 = NULL;
	pars->inquote = 0;
	pars->stop = 0;
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
