/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:29:59 by user42            #+#    #+#             */
/*   Updated: 2021/06/17 17:30:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_path(const char *builtin)
{
	(void)builtin;
	return (false);
}

static void	do_builtin(t_cmd cmd)
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
	else if (check_path(cmd.builtin))
		execpath(cmd);
}

int	create_pipe(int *i, t_cmd *cmd)
{
	int			fds[2];
	__pid_t 	pid;

	if (pipe(fds) != 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		do_builtin(cmd[*i++]);

	}
	else
	{
		do_builtin(cmd[*i]);
	}
	
	
	return (1);
}

void	parse_cmd_array(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd[i].builtin)
	{
		if (cmd[i].pipe == true)
			create_pipe(&i, cmd);
		do_builtin(cmd[i]);
		i++;
	}
}
