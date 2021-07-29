/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:59:56 by user42            #+#    #+#             */
/*   Updated: 2021/07/29 21:11:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin(int i, t_cmd *cmd, char **env_list, bool pipe)
{
	int		len;

	if (cmd[i].fdin == -1)
		return ;
	len = ft_strlen(cmd[i].builtin);
	if (ft_strncmp(cmd[i].builtin, "echo", len + 1) == 0)
		builtin_echo(i, cmd, pipe);
	else if (ft_strncmp(cmd[i].builtin, "cd", len + 1) == 0)
		builtin_cd(i, cmd, pipe);
	else if (ft_strncmp(cmd[i].builtin, "pwd", len + 1) == 0)
		builtin_pwd(i, cmd, pipe);
	else if (ft_strncmp(cmd[i].builtin, "export", len + 1) == 0)
		builtin_export(i, cmd, env_list, pipe);
	else if (ft_strncmp(cmd[i].builtin, "unset", len + 1) == 0)
		builtin_unset(i, cmd, env_list, pipe);
	else if (ft_strncmp(cmd[i].builtin, "env", len + 1) == 0)
		builtin_env(i, cmd, env_list, pipe);
	else if (ft_strncmp(cmd[i].builtin, "exit", len + 1) == 0)
		builtin_exit(i, cmd);
	else
		execpath(i, cmd, env_list, pipe);
}

void	cmd_init(t_cmd *cmd)
{	
	cmd->arg = NULL;
	cmd->builtin = NULL;
	cmd->pipe = false;
	cmd->fdout = 1;
	cmd->fdin = 0;
}
