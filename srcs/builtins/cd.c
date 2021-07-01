/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:52:15 by user42            #+#    #+#             */
/*   Updated: 2021/07/01 12:07:07 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char		*go_back(char *pwd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (pwd[i])
	{
		if (pwd[i] == '/')
			count = i;
		i++;
	}
	return (ft_substr(pwd, 0, count));
}

void		builtin_cd(t_cmd cmd)
{
	char		*pwd = NULL;
	int			size;

	size = 0;
	if (ft_strncmp(cmd.arg[1], ".", 1) == 0 && cmd.arg[1][1] == '\0')
		chdir(getenv("HOME"));
	else if (ft_strncmp(cmd.arg[1], "..", 2) == 0 && cmd.arg[1][2] == '\0')
	{
		while (getcwd(pwd, size) == NULL)
			size++;
		pwd = getcwd(pwd, size);
		chdir(go_back(pwd));
	}
	else
		chdir(go_back(cmd.arg[1]));
}
