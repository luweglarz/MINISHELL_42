/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:39:25 by user42            #+#    #+#             */
/*   Updated: 2021/08/23 21:24:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(int i, t_cmd *cmd, bool pipe)
{
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, PATH_MAX_SHELL);
	g_err = 0;
	write (cmd[i].fdout, buff, ft_strlen(buff));
	write (cmd[i].fdout, "\n", 1);
	free(buff);
	if (pipe == true)
		exit(1);
}
