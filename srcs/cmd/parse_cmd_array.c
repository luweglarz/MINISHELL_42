/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:29:59 by user42            #+#    #+#             */
/*   Updated: 2021/06/21 22:54:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_builtin(t_cmd cmd, char **env_list)
{
	int		len;

	len = ft_strlen(cmd.builtin);
	if (ft_strncmp(cmd.builtin, "echo", len) == 0 && cmd.error == false)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd.builtin, "cd", len) == 0 && cmd.error == false)
		builtin_cd(cmd);
	else if (ft_strncmp(cmd.builtin, "pwd", len) == 0 && cmd.error == false)
		builtin_pwd(cmd);
	else if (ft_strncmp(cmd.builtin, "export", len) == 0 && cmd.error == false)
		builtin_export(cmd);
	else if (ft_strncmp(cmd.builtin, "unset", len) == 0 && cmd.error == false)
		builtin_unset(cmd);
	else if (ft_strncmp(cmd.builtin, "env", len) == 0 && cmd.error == false)
		builtin_env(cmd);
	else if (ft_strncmp(cmd.builtin, "exit", len) == 0 && cmd.error == false)
		builtin_exit(cmd);
	else
		execpath(cmd, env_list);
}

static int	create_pipe(int *i, t_cmd *cmd, char **env_list)
{
	int			fds[2];
	int			k;
	pid_t 		pid1;

	if (pipe(fds) != 0)
		return (-1);
	pid1 = fork();
	if (pid1 < 0)
		return (-1);
	k = *i + 1;
	if (pid1 == 0)
	{

		close (fds[1]);
		dup2(fds[0], 0);
		close (fds[0]);
	//	printf("le builtin2 %s\n", cmd[k].builtin);
		do_builtin(cmd[k], env_list);
	}
	else
	{
		close (fds[0]);
		dup2(fds[1], 1);
		close (fds[1]);
	//	printf("le builtin1 %s\n", cmd[*i].builtin);
		do_builtin(cmd[*i], env_list);
		return 3;
	}
	return (1);
}

void	parse_cmd_array(t_cmd *cmd, char **env_list, int nb_cmd)
{
	int		i;

	i = 0;
	while (i < nb_cmd)
	{
		if (cmd[i].pipe == true)
		{
			create_pipe(&i, cmd, env_list);
			i = i + 2;
		}
		if (i >= nb_cmd)
			break;
		do_builtin(cmd[i], env_list);
		i++;	
	}
}
