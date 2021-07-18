/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 21:47:42 by user42            #+#    #+#             */
/*   Updated: 2021/07/18 05:05:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (cmd)
	{
		if (cmd->arg)
		{
			while (cmd->arg[i])
			{
				free(cmd->arg[i]);
				i++;
			}
			free(cmd->arg);
		}
		if (cmd->builtin)
			free(cmd->builtin);
		cmd = NULL;
	}
}

void	error_errno(t_cmd *cmd, int error_code, bool exit_bool)
{
	char	*error_msg;

	error_msg = strerror(error_code);
	write (2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
	free_cmd(cmd);
	if (exit_bool == true)
		exit(error_code);
}
