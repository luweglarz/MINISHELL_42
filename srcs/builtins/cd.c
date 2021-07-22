/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:52:15 by user42            #+#    #+#             */
/*   Updated: 2021/07/22 16:41:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*go_back(char *pwd)
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

void	builtin_cd(int i, t_cmd *cmd, bool pipe)
{
	char	*pwd;
	int		size;
	int		ret;

	size = 0;
	ret = 1;
	pwd = NULL;
	if (cmd[i].arg[1] == NULL)
		chdir(getenv("HOME"));
	else if (ft_strncmp(cmd[i].arg[1], "/", ft_strlen(cmd[i].arg[1]) + 1) == 0)
		chdir("/");
	else if (ft_strncmp(cmd[i].arg[1], "..", 2) == 0 && cmd[i].arg[1][2] == '\0')
	{
		while (getcwd(pwd, size) == NULL)
			size++;
		pwd = getcwd(pwd, size);
		chdir(go_back(pwd));
	}
	else
	{
		ret = chdir(cmd[i].arg[1]);
		if (ret == -1)
			error_errno(cmd, errno, false);
	}
	if (pipe == true)
		exit(1);
}
