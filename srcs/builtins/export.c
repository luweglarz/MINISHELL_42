/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:55:54 by user42            #+#    #+#             */
/*   Updated: 2021/08/23 18:26:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_arg(t_cmd cmd)
{
	int	i;

	i = 0;
	while (cmd.arg[i])
		i++;
	return (i);
}

int	var_already_exist(t_cmd cmd, char **env_list, int arg_i)
{
	int		i;
	char	**env_names;
	char	*tmp;

	i = 0;
	if (arg_i < count_arg(cmd))
	{
		if (ft_strclen(cmd.arg[arg_i], '=') == -1)
			tmp = ft_substr(cmd.arg[arg_i], 0, ft_strlen(cmd.arg[arg_i]));
		else
			tmp = ft_substr(cmd.arg[arg_i], 0, ft_strclen(cmd.arg[arg_i], '=') - 1);
		env_names = get_env_names(env_list);
		while (env_names[i])
		{
			if (ft_strcmp(tmp, env_names[i]) == 0)
			{
				free_env(nb_env(env_names), env_names);
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

void	display_env_ascii(t_cmd cmd, char **env_list)
{
	char	**var_names;
	char	**var_contents;
	int		i;
	int		j;

	i = 0;
	var_names = get_env_names(env_list);
	var_contents = get_env_content(env_list);
	while (env_list[i])
	{
		j = i + 1;
		while (env_list[j])
		{
			if (ft_strcmp(var_names[i], var_names[j]) > 0)
				swap_env(&var_contents[i],
					&var_contents[j], &var_names[i], &var_names[j]);
			j++;
		}
		i++;
	}
	display_env(cmd, var_names, var_contents, env_list);
	free_env(nb_env(var_names), var_names);
	free_env(nb_env(var_contents), var_contents);
}

void	builtin_export(int i, t_cmd *cmd, t_env_l *env, bool pipe)
{
	int		exist;
	int		arg_index;
	int		nb_arg;

	arg_index = 0;
	nb_arg = count_arg(cmd[i]);
	if (nb_arg > 1)
	{
		while (arg_index++ < nb_arg - 1)
		{
			exist = var_already_exist(cmd[i], env->list, arg_index);
			if (exist > 0)
				change_env_var(env, nb_env(env->list),
					exist, cmd[i].arg[arg_index]);
			else if (exist < 0)
				add_env_var(env, nb_env(env->list), cmd[i].arg[arg_index]);
		}
	}
	else if (count_arg(cmd[i]) == 1)
		display_env_ascii(cmd[i], env->list);
	if (pipe == true)
		exit(1);
}
