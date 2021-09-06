/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:52:15 by user42            #+#    #+#             */
/*   Updated: 2021/09/06 20:42:49 by user42           ###   ########.fr       */
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

int	check_file(char *path)
{
	struct stat	*buf;
	int			res;

	res = 0;
	buf = malloc(sizeof(struct stat) * 1);
	if (stat(path, buf) != 0)
		res = errno;
	free(buf);
	return (res);
}

void	cd_error(int error_code)
{
	char	*error_msg;

	error_msg = strerror(error_code);
	write (2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
}

void	builtin_cd(int i, t_cmd *cmd, bool pipe, t_env_l *env)
{
	char	*pwd;
	char	*path;
	int		res;

	pwd = NULL;
	path = NULL;
	res = check_file(cmd[i].arg[1]);
	if (cmd[i].arg[1] == NULL)
		chdir(ft_getenv("HOME", env->list));
	else if (ft_strncmp(cmd[i].arg[1], "/", ft_strlen(cmd[i].arg[1]) + 1) == 0)
		chdir("/");
	else if (ft_strncmp(cmd[i].arg[1], "..", 2)
		== 0 && cmd[i].arg[1][2] == '\0')
	{
		pwd = getcwd(pwd, PATH_MAX_SHELL);
		path = go_back(pwd);
		chdir(path);
		free(path);
	}
	else if (res > 0)
		cd_error(res);
	else
		chdir(cmd[i].arg[1]);
	if (pipe == true)
		exit(1);
}
