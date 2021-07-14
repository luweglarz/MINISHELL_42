/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:17:20 by user42            #+#    #+#             */
/*   Updated: 2021/07/14 15:13:59 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int check_option(char *arg)
{
	int i;

	i = 1;
	if (arg == NULL)
		return (-1);
	if (arg[0] != '-')
		return (-1);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (-1);
		i++;
	}
	return (1);
}

static void	display_echo(t_cmd cmd)
{
	int	i;

	i = 1;
	if (check_option(cmd.arg[1]) == 1)
	{
		i++;
		while (cmd.arg[i])
		{
			write(cmd.fdout, cmd.arg[i], ft_strlen(cmd.arg[i]));
			if (cmd.arg[i + 1] != NULL)
				write(cmd.fdout, " ", 1);
			i++;
		}
	}
	else
	{
		while (cmd.arg[i] != NULL)
		{
			write(cmd.fdout, cmd.arg[i], ft_strlen(cmd.arg[i]));
			if (cmd.arg[i + 1] != NULL)
				write(cmd.fdout, " ", 1);
			i++;
		}
		write(cmd.fdout, "\n", 1);
	}
}

void	builtin_echo(t_cmd cmd, bool pipe)
{
	pid_t 		pid;
	int			i;

	i = 0;
	if (pipe == false)
	{
		pid = fork();
		if (pid < 0)
			error_errno(&cmd, errno, true);
		if (pid == 0)
		{
			display_echo(cmd);
			exit(1);
		}
		waitpid(pid, NULL, 0);
	}
	else if (pipe == true)
	{
		display_echo(cmd);
		exit(1);
	}
}
