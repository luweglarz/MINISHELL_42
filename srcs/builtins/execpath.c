/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:00:24 by user42            #+#    #+#             */
/*   Updated: 2021/08/23 21:36:10 by user42           ###   ########.fr       */
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

static void	free_splitnjoin(char **split, char *join)
{	
	int	i;

	i = 0;
	(void)join;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	execve_with_path(int index, t_cmd *cmd, char **env_list)
{
	int			i;
	char		**split;
	char		*join;
	struct stat	*buf;

	i = 0;
	buf = malloc(sizeof(struct stat));
	split = ft_split_slash(getenv("PATH"), ':');
	while (split[i])
	{
		join = ft_strjoin(split[i], cmd[index].builtin);
		if (stat(join, buf) == 0)
			execve(join, cmd[index].arg, env_list);
		free(join);
		i++;
	}
	free(buf);
	free_splitnjoin(split, join);
}

static void	execpath_no_pipe(int i, t_cmd *cmd, char **env_list)
{
	if (cmd[i].fdout != 1)
		dup2(cmd[i].fdout, 1);
	if (cmd[i].fdin != 0)
		dup2(cmd[i].fdin, 0);
	if (check_is_path(cmd[i].builtin) == 1)
		execve(cmd[i].builtin, cmd[i].arg, env_list);
	else
		execve_with_path(i, cmd, env_list);
	error_errno(cmd, errno, true);
}

void	execpath(int i, t_cmd *cmd, char **env_list, bool pipe)
{
	pid_t		pid;
	int			status;

	if (pipe == false)
	{
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
			execpath_no_pipe(i, cmd, env_list);
		waitpid(pid, &status, 0);
		g_err = WEXITSTATUS(status);
	}
	else if (pipe == true)
	{
		if (cmd[i].fdout != 1)
			dup2(cmd[i].fdout, 1);
		if (cmd[i].fdin != 0)
			dup2(cmd[i].fdin, 0);
		if (check_is_path(cmd[i].builtin) == 1)
			execve(cmd[i].builtin, cmd[i].arg, env_list);
		else
			execve_with_path(i, cmd, env_list);
		exit(1);
	}
}
