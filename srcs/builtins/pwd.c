/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:39:25 by user42            #+#    #+#             */
/*   Updated: 2021/06/09 16:59:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*builtin_pwd(t_cmd cmd)
{
	int		size;
	char	*buff;

	size = 0;
	buff = NULL;
	(void)cmd;
	while (getcwd(buff, size) == NULL)
		size++;
	printf("%s\n", getcwd(buff, size));
	return (buff);
}