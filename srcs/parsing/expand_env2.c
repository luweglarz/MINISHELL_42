/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 04:46:15 by user42            #+#    #+#             */
/*   Updated: 2021/07/18 04:47:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_tmp(t_cmd *cmd, t_pars *pars)
{
	if (pars->stop == -1)
		pars->tmp = ft_substr(cmd[pars->i].arg[pars->j], 0, pars->index);
	else if (pars->res != NULL)
	{
		if (pars->stop != pars->index)
		{
			pars->var_content = ft_substr(cmd[pars->i].arg[pars->j],
					pars->stop, pars->index - pars->stop);
			pars->tmp = ft_strjoin(pars->res, pars->var_content);
			free(pars->var_content);
			free(pars->res);
			pars->res = NULL;
		}
		else
		{
			pars->tmp = ft_strdup(pars->res);
			free(pars->res);
			pars->res = NULL;
		}
	}
	pars->index++;
	pars->stop = pars->index;
}

void	fill_before_return(t_cmd *cmd, t_pars *pars)
{
	if (pars->tmp == NULL)
	{
		pars->tmp = ft_substr(cmd[pars->i].arg[pars->j],
				pars->stop, ft_strlen(cmd[pars->i].arg[pars->j]));
		pars->var_content = ft_strjoin(pars->res, pars->tmp);
		free(pars->tmp);
		free(pars->res);
		pars->res = ft_strdup(pars->var_content);
		free(pars->var_content);
	}
	if (pars->res != NULL)
	{
		free(cmd[pars->i].arg[pars->j]);
		cmd[pars->i].arg[pars->j] = ft_strdup(pars->res);
		free(pars->res);
		pars->res = NULL;
	}
}

void	get_dollar(t_cmd *cmd, t_pars *pars)
{
	pars->var_content = ft_strdup("$");
	if (cmd[pars->i].arg[pars->j][pars->index] == '\'')
		pars->inquote = 1;
	else if (cmd[pars->i].arg[pars->j][pars->index] == '"'
		&& pars->inquote == 2)
		pars->inquote = 0;
	else if (cmd[pars->i].arg[pars->j][pars->index] == '"'
		&& pars->inquote == 0)
		pars->inquote = 2;
}

void	get_var_content(t_cmd *cmd, t_pars *pars, char **env_list)
{
	while (cmd[pars->i].arg[pars->j][pars->index]
		&& cmd[pars->i].arg[pars->j][pars->index] != '$'
		&& cmd[pars->i].arg[pars->j][pars->index] != '\''
		&& cmd[pars->i].arg[pars->j][pars->index] != '"'
		&& cmd[pars->i].arg[pars->j][pars->index] != '>'
		&& cmd[pars->i].arg[pars->j][pars->index] != '<'
		&& cmd[pars->i].arg[pars->j][pars->index] != '|')
		pars->index++;
	pars->var_name = ft_substr(cmd[pars->i].arg[pars->j],
			pars->stop, pars->index - pars->stop);
	if (pars->inquote == 0)
		pars->var_content = ft_getenv_splited(pars->var_name, env_list);
	else if (pars->inquote == 2)
		pars->var_content = ft_getenv(pars->var_name, env_list);
	pars->stop = pars->index;
	if (cmd[pars->i].arg[pars->j][pars->index] == '\''
		|| cmd[pars->i].arg[pars->j][pars->index] == '"')
		pars->index--;
	if (pars->var_content == NULL)
		pars->var_content = ft_strdup("");
	free(pars->var_name);
	pars->var_name = NULL;
}
