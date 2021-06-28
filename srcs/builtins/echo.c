/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:17:20 by user42            #+#    #+#             */
/*   Updated: 2021/06/28 15:01:19 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_echo(t_cmd cmd, bool pipe)
{
	pid_t 		pid;
	int			i;

	i = 0;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (cmd.arg && ft_strncmp(cmd.arg[1], "-n", 2) == 0)
		{
			cmd.arg[1] +=  2;
			if (cmd.arg[1])
				printf("%s",cmd.arg[1]);
		}
		else if (cmd.error == false)
		{
			if (cmd.arg[1])
				printf("%s", cmd.arg[1]);
			printf("\n");
		}
		exit(1);
	}
	waitpid(pid, NULL, 0);
}