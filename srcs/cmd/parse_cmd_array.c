/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:29:59 by user42            #+#    #+#             */
/*   Updated: 2021/07/29 22:29:58 by user42           ###   ########.fr       */
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
		builtin_exit(i, cmd, pipe);
	else
		execpath(i, cmd, env_list, pipe);
}

void	parse_cmd_array(t_cmd *cmd, char **env_list, int nb_cmd)
{
	int		i;
	int		nb_pipe;

	i = 0;
	while (i < nb_cmd)
	{
		nb_pipe = 0;
		if (cmd[i].pipe == true)
		{
			while (cmd[i + nb_pipe].pipe == true)
				nb_pipe++;
			if (nb_pipe == 1 && cmd[i + 1].builtin != NULL)
				i = single_pipe(i, cmd, env_list);
			else if (nb_pipe > 1)
				i = multi_pipe(i, cmd, env_list, nb_pipe);
			if (i >= nb_cmd)
				break ;
		}
		exec_builtin(i, cmd, env_list, false);
		i++;
	}
}
