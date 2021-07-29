/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:52:15 by user42            #+#    #+#             */
/*   Updated: 2021/07/29 20:35:37 by user42           ###   ########.fr       */
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

void	absolute_path(int i, t_cmd *cmd)
{
	int		ret;

	ret = 1;
	ret = chdir(cmd[i].arg[1]);
	if (ret == -1)
		error_errno(cmd, errno, false);
}

void	builtin_cd(int i, t_cmd *cmd, bool pipe)
{
	char	*pwd;
	char	*path;
	int		size;

	size = 0;
	pwd = NULL;
	path = NULL;
	if (cmd[i].arg[1] == NULL)
		chdir(getenv("HOME"));
	else if (ft_strncmp(cmd[i].arg[1], "/", ft_strlen(cmd[i].arg[1]) + 1) == 0)
		chdir("/");
	else if (ft_strncmp(cmd[i].arg[1], "..", 2)
		== 0 && cmd[i].arg[1][2] == '\0')
	{
		while (getcwd(pwd, size) == NULL)
			size++;
		pwd = getcwd(pwd, size);
		path = go_back(pwd);
		chdir(path);
		free(path);
	}
	else
		absolute_path(i, cmd);
	if (pipe == true)
		exit(1);
}
