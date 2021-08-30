/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:55:54 by user42            #+#    #+#             */
/*   Updated: 2021/08/30 14:32:34 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	var_already_exist(t_cmd cmd, char **env_list, int a_i, int i)
{
	char	**env_names;
	char	*tmp;

	if (a_i < count_arg(cmd))
	{
		if (ft_strclen(cmd.arg[a_i], '=') == -1)
			tmp = ft_substr(cmd.arg[a_i], 0, ft_strlen(cmd.arg[a_i]));
		else
			tmp = ft_substr(cmd.arg[a_i], 0, ft_strclen(cmd.arg[a_i], '='));
		env_names = get_env_names(env_list);
		while (env_names[i])
		{
			if (ft_strcmp(tmp, env_names[i]) == 0)
			{
				free_env(nb_env(env_names), env_names);
				free(tmp);
				return (i);
			}
			i++;
		}
		free(tmp);
		free_env(nb_env(env_names), env_names);
	}
	return (-1);
}

char	**get_env_content(char **env_list)
{
	int		i;
	char	**env_content;

	i = 0;
	env_content = malloc(sizeof(char *) * (nb_env(env_list) + 1));
	while (env_list[i])
	{
		if (ft_strclen(env_list[i], '=')
			== (int)ft_strlen(env_list[i])
			|| ft_strclen(env_list[i], '=') == -1)
			env_content[i] = ft_strdup("");
		else
			env_content[i] = ft_substr(env_list[i],
					ft_strclen(env_list[i], '=') + 1, ft_strlen(env_list[i]));
		i++;
	}
	env_content[i] = NULL;
	return (env_content);
}

void	display_env_ascii(t_cmd cmd, t_env_l *env)
{
	char	**var_names;
	char	**var_contents;
	int		i;
	int		j;

	i = 0;
	var_names = get_env_names(env->list);
	var_contents = get_env_content(env->list);
	while (env->list[i])
	{
		j = i + 1;
		while (env->list[j])
		{
			if (ft_strcmp(var_names[i], var_names[j]) > 0)
				swap_env(&var_contents[i],
					&var_contents[j], &var_names[i], &var_names[j]);
			j++;
		}
		i++;
	}
	display_env(cmd, var_names, var_contents, env);
	free_env(nb_env(var_names), var_names);
	free_env(nb_env(var_contents), var_contents);
}

int	check_env_name(char *cmd)
{
	int		i;
	char	*s;

	i = 0;
	if (ft_strclen(cmd, '=') == -1)
		s = ft_strdup(cmd);
	else
		s = ft_substr(cmd, 0, ft_strclen(cmd, '='));
	while (s[i])
	{
		if (ft_isalnum(s[i]) == 0 && s[i] != '_')
		{
			free(s);
			return (-1);
		}
		i++;
	}
	free(s);
	return (0);
}

void	builtin_export(int i, t_cmd *cmd, t_env_l *env, bool pipe)
{
	int		exist;
	int		arg_index;
	int		nb_arg;

	arg_index = 0;
	nb_arg = count_arg(cmd[i]);
	g_err = 0;
	if (nb_arg > 1)
	{
		while (arg_index++ < nb_arg - 1)
		{
			exist = var_already_exist(cmd[i], env->list, arg_index, 0);
			if (exist > 0)
				change_env_var(env, nb_env(env->list),
					exist, cmd[i].arg[arg_index]);
			else if (exist < 0 && check_env_name(cmd[i].arg[arg_index]) != -1)
				add_env_var(env, nb_env(env->list), cmd[i].arg[arg_index]);
			else
				g_err = 1;
		}
	}
	else if (count_arg(cmd[i]) == 1)
		display_env_ascii(cmd[i], env);
	if (pipe == true)
		exit(1);
}
