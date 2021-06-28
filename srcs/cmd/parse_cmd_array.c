/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:29:59 by user42            #+#    #+#             */
/*   Updated: 2021/06/28 15:02:03 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_builtin(t_cmd cmd, char **env_list, bool pipe)
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
		builtin_export(cmd, pipe);
	else if (ft_strncmp(cmd.builtin, "unset", len) == 0 && cmd.error == false)
		builtin_unset(cmd, pipe);
	else if (ft_strncmp(cmd.builtin, "env", len) == 0 && cmd.error == false)
		builtin_env(cmd, pipe);
	else if (ft_strncmp(cmd.builtin, "exit", len) == 0 && cmd.error == false)
		builtin_exit(cmd, pipe);
	else
		execpath(cmd, env_list, pipe);
}

static void	pipe_ends(int end, t_cmd cmd, int *fds, char **env_list)
{
	if (end == STDIN_FILENO)
	{
		close (fds[1]);
		dup2(fds[0], 0);
		close (fds[0]);
		do_builtin(cmd, env_list, true);
	}
	else if (end == STDOUT_FILENO)
	{
		close (fds[0]);
		dup2(fds[1], 1);
		close (fds[1]);
		do_builtin(cmd, env_list, true);
	}
}

static int	create_pipe(int *i, t_cmd *cmd, char **env_list)
{
	int			fds[2];
	int			k;
	pid_t 		pid1;
	pid_t		pid2;

	if (pipe(fds) == -1)
		return (-1);
	k = *i + 1;
	pid1 = fork();
	if (pid1 == -1)
		return (-1);
	if (pid1 == 0)
	pipe_ends(STDIN_FILENO, cmd[k], fds, env_list);
	pid2 = fork();
	if (pid2 == -1)
		return (-1);
	if (pid2 == 0)
		pipe_ends(STDOUT_FILENO, cmd[*i], fds, env_list);
   	close(fds[0]);
    close(fds[1]);
	waitpid(pid1, NULL, 0);
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
			if (i >= nb_cmd)
			break;
		}
		printf("buil %s\n",cmd[i].builtin);
		do_builtin(cmd[i], env_list, false);
		i++;	
	}
}
