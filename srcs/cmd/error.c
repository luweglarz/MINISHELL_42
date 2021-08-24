/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 21:47:42 by user42            #+#    #+#             */
/*   Updated: 2021/08/24 14:26:53 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int		i;
	int		j;

	i = 0;
	if (cmd)
	{
		if (cmd->arg)
		{
			while (cmd[i].builtin)
			{
				j = 0;
				while (cmd[i].arg[j])
					free(cmd[i].arg[j++]);
				free(cmd[i].arg);
				if (cmd[i].builtin)
					free(cmd[i].builtin);
				i++;
			}
		}
		free(cmd);
		cmd = NULL;
	}
}

void	error_errno(t_cmd *cmd, int error_code, bool exit_bool)
{
	char	*error_msg;

	dprintf(2, "[ERROR_ERRNO] errno = %d\n", errno);
	error_msg = strerror(error_code);
	write (2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
	if (cmd)
		free_cmd(cmd);
	if (exit_bool == true)
		exit(error_code);
}
