/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 04:22:06 by user42            #+#    #+#             */
/*   Updated: 2021/08/05 17:03:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	treat_dollar(t_cmd *cmd, t_pars *pars, char **env_list)
{
	fill_tmp(cmd, pars);
	if (cmd[pars->i].arg[pars->j][pars->index] == '\0'
		|| cmd[pars->i].arg[pars->j][pars->index] == '\''
		|| cmd[pars->i].arg[pars->j][pars->index] == '"'
		|| cmd[pars->i].arg[pars->j][pars->index] == '$')
		get_dollar(cmd, pars);
	else if (cmd[pars->i].arg[pars->j][pars->index] == '?')
	{
		pars->stop = pars->index + 1;
		get_exit_code(pars);
	}
	else
		get_var_content(cmd, pars, env_list);
	if (pars->tmp)
	{
		pars->res = ft_strjoin(pars->tmp, pars->var_content);
		free(pars->tmp);
		pars->tmp = NULL;
	}
	else
		pars->res = ft_strdup(pars->var_content);
	free(pars->var_content);
	pars->var_content = NULL;
}

void	expand_env_arg(t_cmd *cmd, char **env_list, int i, int j)
{
	t_pars	pars;

	init_struct(&pars, i, j);
	while (cmd[i].arg[j][pars.index])
	{
		pars.inquote = check_inquote
			(cmd[pars.i].arg[pars.j][pars.index], pars.inquote);
		if (pars.inquote == 1 || pars.inquote == 2)
			pars.inquote = check_solo_quote
				(&cmd[pars.i].arg[pars.j][pars.index], pars.inquote);
		if (cmd[pars.i].arg[pars.j][pars.index] == '$'
		&& (pars.inquote == 0 || pars.inquote == 2))
			treat_dollar(cmd, &pars, env_list);
		if (cmd[pars.i].arg[pars.j][pars.index] != '$'
		|| (cmd[i].arg[pars.j][pars.index] == '$' && pars.inquote == 1))
			pars.index++;
	}
	fill_before_return(cmd, &pars);
}

void	format_args(t_cmd *cmd, char **env_list, int nb_cmd)
{
	int	i;
	int	j;
	int	dollar;

	i = 0;
	while (i < nb_cmd)
	{
		j = 0;
		while (cmd[i].arg[j])
		{
			dollar = dollar_inside(cmd, i, j);
			if (dollar > 0)
				expand_env_arg(cmd, env_list, i, j);
			j++;
		}
		i++;
	}
}
