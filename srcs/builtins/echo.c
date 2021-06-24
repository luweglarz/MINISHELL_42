/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:17:20 by user42            #+#    #+#             */
/*   Updated: 2021/06/24 12:54:32 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_echo(t_cmd cmd)
{
	pid_t 		pid;
	int			i;

	i = 0;
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (cmd.option && ft_strncmp(cmd.option, "-n", 2) == 0)
		{
			while (cmd.arg[i])
			{
				printf("%s",cmd.arg[i]);
				i++;
			}
		}
		else if (cmd.error == false)
		{
			while (cmd.arg[i])
			{
				printf("%s", cmd.arg[i]);
				i++;
			}
			printf("\n");
		}
		exit(1);
	}
	waitpid(pid, NULL, 0);
}