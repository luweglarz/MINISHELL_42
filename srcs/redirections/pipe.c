/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 21:40:40 by user42            #+#    #+#             */
/*   Updated: 2021/09/25 17:46:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	pipe_stdout(int i, t_cmd *cmd, int *fds, t_env_l *env)
{
	dprintf(2,"le buil stdout %s\n", cmd[i].builtin);
	close (fds[0]);
	dup2(fds[1], 1);
	close (fds[1]);
	exec_builtin(i, cmd, env, true);
}

static void	pipe_stdin(int i, t_cmd *cmd, int *fds, t_env_l *env)
{
	dprintf(2,"le buil stdin %s\n", cmd[i].builtin);
	close (fds[1]);
	dup2(fds[0], 0);
	close (fds[0]);
	exec_builtin(i + 1, cmd, env, true);
}

int	single_pipe(int i, t_cmd *cmd, t_env_l *env)
{
	int			fds[2];
	pid_t		pid1;
	pid_t		pid2;

	if (pipe(fds) == -1)
		error_errno(cmd, errno, true, env);
	pid1 = fork();
	if (pid1 == -1)
		error_errno(cmd, errno, true, env);
	if (pid1 == 0)
		pipe_stdin(i, cmd, fds, env);
	pid2 = fork();
	if (pid2 == -1)
		error_errno(cmd, errno, true, env);
	if (pid2 == 0)
		pipe_stdout(i, cmd, fds, env);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (i + 2);
}

static void	set_pipe(int i, t_cmd *cmd, int fds[2])
{
	if (i != 0)
		dup2(fds[0], 0);
	close(fds[0]);
	if (cmd[i + 1].builtin != NULL)
	{
		dup2(fds[1], 1);
		close(fds[1]);
	}
	else
		close(fds[1]);
}


int	multi_pipe(int i, t_cmd *cmd, t_env_l *env, int nb_pipe)
{
	int		fds[2];
	pid_t	*pid;

	nb_pipe++;
	pid = malloc(sizeof(pid_t) * nb_pipe);
	while (nb_pipe-- != 0)
	{
		pipe(fds);
		pid[i] = fork();
		if (pid[i] == -1)
			return (-1);
		if (pid[i] == 0)
		{
			set_pipe(i, cmd, fds);
			exec_builtin(i, cmd, env, true);
		}
		close(fds[1]);
		close(fds[0]);
		i++;
	}
	close(fds[0]);
	close(fds[1]);
	nb_pipe = i;
	i = 0;
	while (i++ < nb_pipe)
	waitpid(pid[i], NULL, 0);
	return (i);
}
