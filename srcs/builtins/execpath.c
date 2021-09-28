/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:00:24 by user42            #+#    #+#             */
/*   Updated: 2021/09/28 14:23:37 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_err = 0;

static int	check_is_path(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static void	execve_with_path(int index, t_cmd *cmd, t_env_l *env)
{
	int			i;
	char		**split;
	char		*join;
	struct stat	*buf;

	i = 0;
	buf = malloc(sizeof(struct stat));
	split = ft_split_slash(ft_getenv("PATH", env->list), ':');
	if (split == NULL)
	{
		join = ft_strdup("");
		execve(join, cmd[index].arg, env->list);
		error_errno(cmd, errno, true, env);
	}
	while (split[i])
	{
		join = ft_strjoin(split[i], cmd[index].builtin);
		if (stat(join, buf) == 0)
			execve(join, cmd[index].arg, env->list);
		i++;
	}
	free(buf);
	if (split)
		free_split_join(split, join);
}

static void	execpath_no_pipe(int i, t_cmd *cmd, t_env_l *env)
{
	if (cmd[i].fdout != 1)
		dup2(cmd[i].fdout, 1);
	if (cmd[i].fdin != 0)
		dup2(cmd[i].fdin, 0);
	if (check_is_path(cmd[i].builtin) == 1)
		execve(cmd[i].builtin, cmd[i].arg, env->list);
	else
		execve_with_path(i, cmd, env);
	error_errno(cmd, errno, true, env);
}

void	execpath_pipe(t_cmd *cmd, int i, t_env_l *env)
{
	if (cmd[i].fdout != 1)
		dup2(cmd[i].fdout, 1);
	if (cmd[i].fdin != 0)
		dup2(cmd[i].fdin, 0);
	if (check_is_path(cmd[i].builtin) == 1)
		execve(cmd[i].builtin, cmd[i].arg, env->list);
	else
		execve_with_path(i, cmd, env);
	error_errno(cmd, errno, true, env);
}

void	execpath(int i, t_cmd *cmd, t_env_l *env, bool pipe)
{
	pid_t		pid;
	int			status;

	if (pipe == false)
	{
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
			execpath_no_pipe(i, cmd, env);
		waitpid(pid, &status, 0);
		if (ft_strlen(cmd[i].arg[0]) != 0)
			g_err = WEXITSTATUS(status);
	}
	else if (pipe == true)
		execpath_pipe(cmd, i, env);
}
