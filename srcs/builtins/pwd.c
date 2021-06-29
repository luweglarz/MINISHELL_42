/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:39:25 by user42            #+#    #+#             */
/*   Updated: 2021/06/28 16:30:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_pwd(bool pipe)
{
	int		size;
	char	*buff;

	size = 0;
	buff = NULL;
	(void)pipe;
	while (getcwd(buff, size) == NULL)
		size++;
	printf("%s\n", getcwd(buff, size));
}