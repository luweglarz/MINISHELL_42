/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 21:47:42 by user42            #+#    #+#             */
/*   Updated: 2021/06/25 22:52:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error(t_cmd *cmd, int error)
{
	printf("errorrrrr %d\n", error);
	if (error = EXECVE_ERROR)
		write (2, "Execve couldn't execute your command", 36);
	if (cmd->arg)
		free(cmd->arg);
	if (cmd->builtin)
		free(cmd->builtin);
	exit(error);
}