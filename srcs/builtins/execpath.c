/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:00:24 by user42            #+#    #+#             */
/*   Updated: 2021/07/18 17:22:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	execve_with_path(t_cmd cmd, char **env_list)
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
		join = ft_strjoin(split[i], cmd.builtin);
		if (stat(join, buf) == 0)
			execve(join, cmd.arg, env_list);
		free(join);
		i++;
	}
	free(buf);
	free_splitnjoin(split, join);
}

static void	execpath_no_pipe(t_cmd cmd, char **env_list)
{
	if (cmd.fdout != 1)
		dup2(cmd.fdout, 1);
	if (cmd.fdin != 0)
		dup2(cmd.fdin, 0);
	if (check_is_path(cmd.builtin) == 1)
		execve(cmd.builtin, cmd.arg, env_list);
	else
		execve_with_path(cmd, env_list);
	error_errno(&cmd, errno, true);
}

void	execpath(t_cmd cmd, char **env_list, bool pipe)
{
	pid_t		pid;

	if (pipe == false)
	{
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
			execpath_no_pipe(cmd, env_list);
		waitpid(pid, NULL, 0);
	}
	else if (pipe == true)
	{
		if (cmd.fdout != 1)
			dup2(cmd.fdout, 1);
		if (cmd.fdin != 0)
			dup2(cmd.fdin, 0);
		if (check_is_path(cmd.builtin) == 1)
			execve(cmd.builtin, cmd.arg, env_list);
		else
			execve_with_path(cmd, env_list);
		error_errno(&cmd, errno, true);
	}
}
