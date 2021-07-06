/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:59:56 by user42            #+#    #+#             */
/*   Updated: 2021/07/06 17:29:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_builtin(t_cmd cmd, char **env_list, bool pipe)
{
	int		len;

	len = ft_strlen(cmd.builtin);
	if (ft_strncmp(cmd.builtin, "echo", len) == 0 && cmd.error == false)
		builtin_echo(cmd, pipe);
	else if (ft_strncmp(cmd.builtin, "cd", len) == 0 && cmd.error == false)
		builtin_cd(cmd, pipe);
	else if (ft_strncmp(cmd.builtin, "pwd", len) == 0 && cmd.error == false)
		builtin_pwd(pipe);
	else if (ft_strncmp(cmd.builtin, "export", len) == 0 && cmd.error == false)
		builtin_export(cmd, env_list);
	else if (ft_strncmp(cmd.builtin, "unset", len) == 0 && cmd.error == false)
		builtin_unset(cmd, env_list);
	else if (ft_strncmp(cmd.builtin, "env", len) == 0 && cmd.error == false)
		builtin_env(cmd, env_list);
	else if (ft_strncmp(cmd.builtin, "exit", len) == 0 && cmd.error == false)
		builtin_exit(cmd);
	else
		execpath(cmd, env_list, pipe);
}

void	cmd_init(t_cmd *cmd)
{	
	cmd->arg = NULL;
	cmd->builtin = NULL;
	cmd->error = false;
	cmd->pipe = false;
}
