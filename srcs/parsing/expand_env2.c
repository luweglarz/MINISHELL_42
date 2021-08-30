/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 15:58:24 by user42            #+#    #+#             */
/*   Updated: 2021/08/30 23:52:20 by user42           ###   ########.fr       */
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

int	ft_getenv_index(char *var_name, char **env_list)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env_list[i])
	{
		if (env_list[i] && ft_strncmp(env_list[i], var_name, len) == 0
			&& env_list[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*join_tokens(t_env_l *env, int index)
{
	int i;
	int len;
	char *joined;
	char *tmp;

	joined = ft_strdup(env->token[index][0]);
	len = 0;
	while (env->token[index][len])
		len++;
	i = 1;
	while (i < len)
	{
		printf("DEBUG token[%d]=%s\n", i, env->token[index][i]);
		tmp = ft_strjoin(joined, " ");
		free(joined);
		joined = ft_strjoin(tmp, env->token[index][i]);
		free(tmp);
		i++;
	}
	return (joined);
}

char	*name_to_tokens(char *line, int *i, t_env_l *env)
{
	int		j;
	int		index;
	char	*name;
	char	*content;

	j = 0;
	index = 0;
	while (line[j] && (ft_isalnum(line[j]) == 1 || line[j] == '_'))
		j++;
	if (j == 0)
		content = ft_strdup("");
	else
	{
		name = ft_substr(line, 0, j);
		index = ft_getenv_index(name, env->list);
		free(name);
		if (index == -1 || !env->token[index][0])
			content = ft_strdup("");
		else
			content = join_tokens(env, index);
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
