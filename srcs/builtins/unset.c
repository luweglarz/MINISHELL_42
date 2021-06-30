/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:56:37 by user42            #+#    #+#             */
/*   Updated: 2021/06/30 13:46:28 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_env_names(char **env_list)
{
	int i;
	char **env_names;

	i = 0;
	env_names = malloc(sizeof(char *) * (nb_env(env_list) + 1));
	while (env_list[i])
	{
		env_names[i] = ft_substr(env_list[i], 0, ft_strclen(env_list[i], '='));
		i++;
	}
	env_names[i] = NULL;
	return (env_names);
}

int	var_exist(t_cmd cmd, char **env_list)
{
	int i;
	char **env_names;

	i = 0;
	while (cmd.arg[i])
		i++;
	if (i > 1)
		return (-2);
	else if (i == 1)
	{
		env_names = get_env_names(env_list);
		i = 0;
		while (env_names[i])
		{
			if (ft_strcmp(cmd.arg[0], env_names[i]) == 0)
			{
				free_env(nb_env(env_names), env_names);
				return (i);
			}
			i++;
		}
		free_env(nb_env(env_names), env_names);
	}
	return (-1);
}

void		builtin_unset(t_cmd cmd, char **env_list)
{
	char **tmp;
	int	to_del;
	int i;
	int len;

	i = 0;
	to_del = var_exist(cmd, env_list);
	len = nb_env(env_list);
	if (to_del > 0)
	{
		//je malloc tmp;
		tmp = malloc(sizeof(char *) * len);
		//je copy dans tmp les variables avant celle a supprimer.
		while (i < to_del)
		{
			tmp[i] = ft_strdup(env_list[i]);
			i++;
		}
		printf("La ligne a delete est : %s\n", env_list[i]);
		//je copy dans tmp les variables apres celle a supprimer.
		while (env_list[i + 1])
		{
			tmp[i] = ft_strdup(env_list[i + 1]);
			i++;
		}
		tmp[i] = NULL;
		//je free env_list
		i = 0;
		while (env_list[i])
		{
			if (env_list[i])
			{
				free(env_list[i]);
				env_list[i] = NULL;
			}
			i++;
		}
		free(*env_list);
		*env_list = malloc(sizeof(char *) * len);
		//je duplique tmp dans env_list;
		i = 0;
		while (tmp[i])
		{
			env_list[i] = ft_strdup(tmp[i]);
			i++;
		}
		env_list[i] = NULL;
		//je free tmp;
		i = 0;
		while (tmp[i])
		{
			if (tmp[i])
			{
				free(tmp[i]);
				tmp[i] = NULL;
			}
			i++;
		}
		free(tmp);
	}
	else if (to_del == -2)
		printf("La fonction \"env\" ne peut prendre qu'un parametre.\n");
}