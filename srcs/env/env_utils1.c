/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:21:19 by user42            #+#    #+#             */
/*   Updated: 2021/07/18 16:41:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	nb_env(char **env_list)
{
	int	i;

	i = 0;
	while (env_list[i])
		i++;
	return (i);
}

void	free_env(int nb_env, char **env_list)
{
	int	i;

	i = 0;
	while (i < nb_env)
	{
		if (env_list[i])
		{
			free(env_list[i]);
			env_list[i] = NULL;
		}
		i++;
	}
	free(env_list);
}

void	free_env_list(int nb_env, char **env_list)
{
	int	i;

	i = 0;
	while (i < nb_env)
	{
		if (env_list[i])
		{
			free(env_list[i]);
			env_list[i] = NULL;
		}
		i++;
	}
	free(*env_list);
}

char	**init_env(char **envp, int ac, char **av)
{
	char	**env_list;
	int		i;

	(void)ac;
	(void)av;
	i = 0;
	while (envp[i] != NULL)
		i++;
	env_list = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i] != NULL)
	{
		env_list[i] = ft_strdup(envp[i]);
		i++;
	}
	env_list[i] = NULL;
	return (env_list);
}

char	*ft_getenv(char *var_name, char **env_list)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env_list[i] != NULL)
	{
		if (env_list[i] && ft_strncmp(env_list[i], var_name, len) == 0
			&& env_list[i][len] == '=')
			return (ft_substr(env_list[i], len + 1, ft_strlen(env_list[i])));
		i++;
	}
	return (NULL);
}
