/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:17:20 by user42            #+#    #+#             */
/*   Updated: 2021/07/06 19:24:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	display_echo(t_cmd cmd)
{
	int	i;

	i = 1;
	if (cmd.arg && ft_strncmp(cmd.arg[1], "-n", 2) == 0 && cmd.arg[1][2] == '\0')
	{
		i++;
		while (cmd.arg[i])
		{
			printf("%s",cmd.arg[i]);
			printf(" ");
				i++;
		}
	}
	else
	{
		while (cmd.arg[i] != NULL)
		{
			printf("%s", cmd.arg[i]);
			printf(" ");
			i++;
		}
		printf("\n");
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
			return ;
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
