/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 21:55:54 by user42            #+#    #+#             */
/*   Updated: 2021/06/30 13:47:42 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	var_already_exist(t_cmd cmd, char **env_list)
{
	int i;
	char **env_names;
	char *tmp;

	i = 0;
	while (cmd.arg[i])
		i++;
	if (i > 1)
		return (-2);
	else if (i == 1)
	{
		if (ft_strclen(cmd.arg[0], '=') == -1)
			return (-3);
		tmp = ft_substr(cmd.arg[0], 0, ft_strclen(cmd.arg[0], '='));
		printf("DEBUG : %s\n", tmp);
		env_names = get_env_names(env_list);
		i = 0;
		while (env_names[i])
		{
			if (ft_strcmp(tmp, env_names[i]) == 0)
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

void		builtin_export(t_cmd cmd, char **env_list)
{
	char **tmp;
	int	exist;
	int i;
	int len;

	i = 0;
	exist = var_already_exist(cmd, env_list);
	printf("exist = %d\n", exist);
	len = nb_env(env_list);
	//si je dois modifier une var
	if (exist > 0)
	{
		//je malloc tmp;
		tmp = malloc(sizeof(char *) * len + 1);
		//je copy dans tmp les variables avant celle a supprimer.
		while (i < exist)
		{
			tmp[i] = ft_strdup(env_list[i]);
			i++;
		}
		tmp[i] = ft_strdup(cmd.arg[0]);
		printf("La ligne a modifier est : %s\n", env_list[i]);
		i++;
		//je copy dans tmp les variables apres celle a supprimer.
		while (env_list[i])
		{
			tmp[i] = ft_strdup(env_list[i]);
			i++;
		}
		tmp[i] = NULL;
		//je free env_list
		i = 0;
		while (env_list[i])
		{
			if (env_list[i])
			{
				//printf("FREE ENV : [%d]%s\n", i, env_list[i]);
				free(env_list[i]);
				env_list[i] = NULL;
			}
			i++;
		}
		free(*env_list);
		*env_list = malloc(sizeof(char *) * len + 1);
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
				//printf("FREE TMP : [%d]%s\n", i, env_list[i]);
				free(tmp[i]);
				tmp[i] = NULL;
			}
			i++;
		}
		free(tmp);
	}
	//si je dois creer une var
	else if (exist == -1)
	{
		//je malloc tmp;
		tmp = malloc(sizeof(char *) * len + 2);
		//je copy dans tmp les variables de env_list
		while (env_list[i])
		{
			tmp[i] = ft_strdup(env_list[i]);
			i++;
		}
		tmp[i] = ft_strdup(cmd.arg[0]);
		printf("La ligne a rajouter est : %s\n", tmp[i]);
		i++;
		tmp[i] = NULL;
		//je free env_list
		i = 0;
		while (env_list[i])
		{
			if (env_list[i])
			{
				//printf("FREE ENV : [%d]%s\n", i, env_list[i]);
				free(env_list[i]);
				env_list[i] = NULL;
			}
			i++;
		}
		free(*env_list);
		*env_list = malloc(sizeof(char *) * len + 2);
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
				//printf("FREE TMP : [%d]%s\n", i, env_list[i]);
				free(tmp[i]);
				tmp[i] = NULL;
			}
			i++;
		}
		free(tmp);
	}
	else if (exist == -2)
		printf("La fonction \"export\" ne peut prendre qu'un parametre.\n");
	else if (exist == -3)
		printf("Mauvais format pour la fonction \"export\".\n");
}