/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:39:25 by user42            #+#    #+#             */
/*   Updated: 2021/07/08 23:02:35 by user42           ###   ########.fr       */
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
	write (cmd.fd, buff, ft_strlen(buff));
	write (cmd.fd, "\n", 1);
	if (pipe == true)
		exit(1);
}
