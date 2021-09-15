/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 21:47:42 by user42            #+#    #+#             */
/*   Updated: 2021/09/16 00:29:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int		i;
	int		j;

	i = 0;
	if (cmd)
	{
		if (cmd->arg)
		{
			while (cmd[i].builtin)
			{
				j = 0;
				while (cmd[i].arg[j])
					free(cmd[i].arg[j++]);
				free(cmd[i].arg);
				if (cmd[i].builtin)
					free(cmd[i].builtin);
				i++;
			}
		}
		free(cmd);
		cmd = NULL;
	}
}

void	exit_free_env(t_env_l *env, int nb)
{
	int	i;
	int	j;

	i = 0;
	while (env->list[i])
	{
		free(env->list[i]);
		i++;
	}
	free(env->list);
	i = 0;
	while (env->token[i])
	{
		j = 0;
		while (env->token[i][j])
		{
			free(env->token[i][j]);
			j++;
		}
		free(env->token[i]);
		i++;
	}
	free(env->token);
	exit(nb);
}

void	error_errno(t_cmd *cmd, int error_code, bool exit_bool, t_env_l *env)
{
	char	*error_msg;

	error_msg = strerror(error_code);
	write (2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
	if (cmd)
		free_cmd(cmd);
	if (exit_bool == true)
		exit_free_env(env, error_code);
}
