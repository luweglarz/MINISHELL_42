/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 04:46:23 by user42            #+#    #+#             */
/*   Updated: 2021/07/20 20:04:40 by user42           ###   ########.fr       */
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

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
}

char	*ft_getenv_splited(char *var_name, char **env_list)
{
	char	*str;
	char	*res;
	char	*tmp;
	char	**tab;
	int		i;

	i = 0;
	str = ft_getenv(var_name, env_list);
	res = NULL;
	if (str == NULL)
		return (NULL);
	else
	{
		tab = ft_split(str, ' ');
		free(str);
		str = NULL;
		tmp = ft_strdup(tab[i]);
		i++;
		while (tab[i])
		{
			if (i == 1)
			{
				str = ft_strjoin(tmp, " ");
				free(tmp);
			}
			else
			{
				str = ft_strjoin(res, " ");
				free(res);
			}
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

void	get_exit_code(t_pars *pars)
{
	pars->var_content = ft_strdup("1");
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
