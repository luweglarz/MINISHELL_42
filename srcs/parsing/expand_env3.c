/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 04:46:23 by user42            #+#    #+#             */
/*   Updated: 2021/08/05 15:05:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	dollar_inside(t_cmd *cmd, int i, int j)
{
	int	index;
	int	inquote;
	int	nb;

	nb = 0;
	inquote = 0;
	index = 0;
	while (cmd[i].arg[j][index])
	{
		inquote = check_inquote(cmd[i].arg[j][index], inquote);
		if (inquote == 1)
			inquote = check_solo_quote(&cmd[i].arg[j][index], inquote);
		if (cmd[i].arg[j][index] == '$' && inquote != 1)
			nb++;
		index++;
	}
	return (nb);
}

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
		if (res == NULL)
			res = ft_strdup(tmp);
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
