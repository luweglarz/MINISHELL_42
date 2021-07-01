/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:59:56 by user42            #+#    #+#             */
/*   Updated: 2021/07/01 12:08:22 by lweglarz         ###   ########.fr       */
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
		builtin_cd(cmd);
	else if (ft_strncmp(cmd.builtin, "pwd", len) == 0 && cmd.error == false)
		builtin_pwd(pipe);
	else if (ft_strncmp(cmd.builtin, "export", len) == 0 && cmd.error == false)
		builtin_export(cmd, pipe);
	else if (ft_strncmp(cmd.builtin, "unset", len) == 0 && cmd.error == false)
		builtin_unset(cmd, pipe);
	else if (ft_strncmp(cmd.builtin, "env", len) == 0 && cmd.error == false)
		builtin_env(cmd, pipe);
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
