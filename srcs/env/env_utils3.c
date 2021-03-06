/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 21:33:43 by user42            #+#    #+#             */
/*   Updated: 2021/08/31 19:13:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_env_l *env)
{
	int	i;
	int	j;

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
}

void	add_env_var(t_env_l *env, int len, char *add)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (len + 2));
	envdup_plus(tmp, env->list, add);
	while (env->list[i])
	{
		free(env->list[i]);
		i++;
	}
	free(env->list);
	env->list = malloc(sizeof(char *) * (len + 2));
	envdup(env->list, tmp);
	free_env(len + 2, tmp);
	free_token(env);
	init_token(env);
}

void	change_env_var(t_env_l *env, int len, int exist, char *change)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * len + 1);
	envdup_n_change(tmp, env->list, change, exist);
	while (env->list[i])
	{
		free(env->list[i]);
		i++;
	}
	free(env->list);
	env->list = malloc(sizeof(char *) * len + 1);
	envdup(env->list, tmp);
	free_env(len, tmp);
	free_token(env);
	init_token(env);
}

int	check_equal(char *var_name, char **env_list)
{
	int	i;

	i = 0;
	while (env_list[i])
	{
		if (ft_strcmp(var_name, env_list[i]) == 0)
		{
			if (ft_strclen(env_list[i], '=') == -1)
				return (-1);
		}
		else if (ft_strncmp(var_name, env_list[i], ft_strlen(var_name)) == 0)
		{
			if (ft_strclen(env_list[i], '=') > 0
				&& ft_strclen(env_list[i], '=') == (int)ft_strlen(env_list[i]))
				return (-2);
		}
		i++;
	}
	return (1);
}

void	display_env(t_cmd cmd, char **var_names
	, char **var_contents, t_env_l *env)
{
	int	i;
	int	equal;

	i = 0;
	while (var_names[i])
	{
		equal = 0;
		write(cmd.fdout, "declare -x ", 11);
		write(cmd.fdout, var_names[i], ft_strlen(var_names[i]));
		if (check_equal(var_names[i], env->list) == -1)
			equal = -1;
		else if (check_equal(var_names[i], env->list) == -2)
			equal = -2;
		if (equal != -1)
		{
			write(cmd.fdout, "=", 1);
			write(cmd.fdout, "\"", 1);
			write(cmd.fdout, var_contents[i], ft_strlen(var_contents[i]));
			write(cmd.fdout, "\"", 1);
		}
		write(cmd.fdout, "\n", 1);
		i++;
	}
}
