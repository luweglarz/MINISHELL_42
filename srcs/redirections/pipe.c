/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 21:40:40 by user42            #+#    #+#             */
/*   Updated: 2021/07/29 20:54:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	pipe_stdout(int i, t_cmd *cmd, int *fds, char **env_list)
{
	close (fds[0]);
	dup2(fds[1], 1);
	close (fds[1]);
	exec_builtin(i, cmd, env_list, true);
}

static void	pipe_stdin(int i, t_cmd *cmd, int *fds, char **env_list)
{
	close (fds[1]);
	dup2(fds[0], 0);
	close (fds[0]);
	exec_builtin(i + 1, cmd, env_list, true);
}

int	single_pipe(int i, t_cmd *cmd, char **env_list)
{
	int			fds[2];
	pid_t		pid1;
	pid_t		pid2;

	if (pipe(fds) == -1)
		error_errno(cmd, errno, true);
	pid1 = fork();
	if (pid1 == -1)
		error_errno(cmd, errno, true);
	if (pid1 == 0)
		pipe_stdin(i, cmd, fds, env_list);
	pid2 = fork();
	if (pid2 == -1)
		error_errno(cmd, errno, true);
	if (pid2 == 0)
		pipe_stdout(i, cmd, fds, env_list);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (i + 2);
}

static void	set_pipe(int i, t_cmd *cmd, int fd, int fds[2])
{
	dup2(fd, 0);
	if (cmd[i + 1].builtin != NULL)
		dup2(fds[1], 1);
	else
		close(fds[1]);
	close(fds[0]);
}

int	multi_pipe(int i, t_cmd *cmd, char **env_list, int nb_pipe)
{
	int		fds[2];
	int		fd;
	pid_t	pid;

	fd = 0;
	nb_pipe++;
	while (nb_pipe-- != 0)
	{
		pipe (fds);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			set_pipe(i, cmd, fd, fds);
			exec_builtin(i, cmd, env_list, true);
		}
		waitpid(pid, NULL, 0);
		close(fds[1]);
		fd = fds[0];
		i++;
	}
	return (i);
}