/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 20:52:08 by user42            #+#    #+#             */
/*   Updated: 2021/07/01 12:20:08 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_inquote(const char *line, int i, int inquote)
{
	if (line[i] == '\'' && inquote == 0)
		return (1);
	else if (line[i] == '"' && inquote == 0)
		return (2);
	else if (line[i] == '\'' && inquote == 1)
		return (0);
	else if (line[i] == '"' && inquote == 2)
		return (0);
	else
		return (inquote);
}

int	check_sep(const char *line)
{
	int	i;
	int	inquote;

	i = 0;
	inquote = 0;
	while (line[i])
	{
		inquote = check_inquote(line, i, inquote);
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
}
