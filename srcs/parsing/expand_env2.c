/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 15:58:24 by user42            #+#    #+#             */
/*   Updated: 2021/08/27 16:03:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*name_to_value(char *line, int *i, char **env_list)
{
	int		j;
	char	*name;
	char	*content;

	j = 0;
	while (line[j] && (ft_isalnum(line[j]) == 1 || line[j] == '_'))
		j++;
	if (j == 0)
		content = ft_strdup("");
	else
	{
		name = ft_substr(line, 0, j);
		content = ft_getenv(name, env_list);
		free(name);
		if (content == NULL)
			content = ft_strdup("");
	}
	*i = *i + j;
	return (content);
}

void	get_front_buffer(t_pars *exp, char *line)
{
	if (exp->stop == -1 && exp->i > 0)
		exp->newline = ft_substr(line, 0, exp->i);
	else if (exp->stop == -1 && exp->i == 0)
		exp->newline = ft_strdup("");
	exp->remember = exp->i;
	exp->i++;
}

void	get_median_buffer(t_pars *exp, char *line)
{
	exp->tmp = ft_strdup(exp->newline);
	free(exp->newline);
	exp->save = ft_substr(line, exp->stop, exp->remember - exp->stop);
	exp->newline = ft_strjoin(exp->tmp, exp->save);
	free(exp->save);
	free(exp->tmp);
}

void	get_back_buffer(t_pars *exp, char *line)
{
	exp->tmp = ft_strdup(exp->newline);
	free(exp->newline);
	exp->save = ft_substr(line, exp->stop, exp->i - exp->stop);
	exp->newline = ft_strjoin(exp->tmp, exp->save);
	free(exp->tmp);
	free(exp->save);
}
