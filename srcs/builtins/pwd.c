/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:39:25 by user42            #+#    #+#             */
/*   Updated: 2021/07/09 17:26:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(t_cmd cmd, bool pipe)
{
	int		size;
	char	*buff;

	size = 0;
	buff = NULL;
	while (getcwd(buff, size) == NULL)
		size++;
	buff = getcwd(buff, size);
	write (cmd.fdout, buff, ft_strlen(buff));
	write (cmd.fdout, "\n", 1);
	if (pipe == true)
		exit(1);
}
