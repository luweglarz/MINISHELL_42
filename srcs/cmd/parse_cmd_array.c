/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:29:59 by user42            #+#    #+#             */
/*   Updated: 2021/06/21 12:33:29 by ugtheven         ###   ########.fr       */
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
	pid_t 	pid;

	if (pipe(fds) != 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		close (fds[1]);
		dup2(fds[0], 0);
		close (fds[0]);
		i++;
		printf("le builtin1 %s\n", cmd[*i].builtin);
		do_builtin(cmd[*i], env_list);
		exit(1);
	}
	else
	{
		close (fds[0]);
		dup2(fds[1], 1);
		close (fds[1]);
		printf("le builtin2 %s\n", cmd[*i].builtin);
		do_builtin(cmd[*i], env_list);
		return (3);
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
			printf("cmdi %s\n", cmd[i].builtin);
			create_pipe(&i, cmd, env_list);
			i++;
		}
		do_builtin(cmd[i], env_list);
		i++;	
	}
}
