/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 04:46:23 by user42            #+#    #+#             */
/*   Updated: 2021/08/23 19:06:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	join_splited_tokens(char **tmp, char **str, char **res, int i)
{
	if (i == 1)
	{
		*str = ft_strjoin(*tmp, " ");
		free(*tmp);
	}
	else
	{
		*str = ft_strjoin(*res, " ");
		free(*res);
	}
}

char	**fill_tmp_tab(char **str, char **tmp)
{
	char	**tab;

	tab = ft_split(*str, ' ');
	free(*str);
	if (tab[0])
		*tmp = ft_strdup(tab[0]);
	return (tab);
}

void	fill_res(char **tmp, char **res)
{
	if (*res == NULL)
	{
		*res = ft_strdup(*tmp);
		free(*tmp);
	}
}

char	*ft_getenv_splited(char *var_name, char **env_list, int i)
{
	char	*str;
	char	*res;
	char	*tmp;
	char	**tab;

	str = ft_getenv(var_name, env_list);
	res = NULL;
	if (str == NULL)
		return (NULL);
	else
	{
		tab = fill_tmp_tab(&str, &tmp);
		while (tab[i])
		{
			join_splited_tokens(&tmp, &str, &res, i);
			res = ft_strjoin(str, tab[i]);
			free(str);
			i++;
		}
		fill_res(&tmp, &res);
		free_tab(tab);
		return (res);
	}
}

void	init_struct(t_pars *pars, int i, int j)
{
	pars->var_content = NULL;
	pars->var_name = NULL;
	pars->tmp = NULL;
	pars->res = NULL;
	pars->index = 0;
	pars->stop = -1;
	pars->inquote = 0;
	pars->i = i;
	pars->j = j;
}
