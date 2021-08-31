/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 15:58:17 by user42            #+#    #+#             */
/*   Updated: 2021/08/31 14:53:49 by ugtheven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_exp(t_pars *exp)
{
	exp->i = 0;
	exp->inquote = 0;
	exp->stop = -1;
	exp->remember = -1;
}

void	add_expanded(t_pars *exp, char *line)
{
	if (exp->stop != -1 && exp->remember - exp->stop > 0)
		get_median_buffer(exp, line);
	exp->stop = exp->i;
	exp->tmp = ft_strdup(exp->newline);
	free(exp->newline);
	exp->newline = ft_strjoin(exp->tmp, exp->expanded);
	free(exp->tmp);
	free(exp->expanded);
}

void	treat_dollar(t_pars *exp, char *line, t_env_l *env)
{
	if (line[exp->i] && (ft_isalnum(line[exp->i + 1]) != 1
			&& line[exp->i + 1] != '_' && line[exp->i + 1] != '?'))
		exp->i++;
	else if (line[exp->i] && (ft_isalnum(line[exp->i + 1]) == 1
			|| line[exp->i + 1] == '_' || line[exp->i + 1] == '?'))
	{
		get_front_buffer(exp, line);
		if (line[exp->i] == '?')
		{
			exp->i++;
			exp->expanded = ft_itoa(g_err);
		}
		else if (exp->inquote == 0)
			exp->expanded = name_to_tokens(&line[exp->i], &exp->i, env);
		else
			exp->expanded = name_to_value(&line[exp->i], &exp->i, env->list);
		if (exp->expanded != NULL)
			add_expanded(exp, line);
	}
}

char	*expand_env_value(t_pars *exp, char *line, t_env_l *env)
{
	init_exp(exp);
	while (line[exp->i])
	{
		exp->inquote = check_inquote(line[exp->i], exp->inquote);
		if (exp->inquote == 1 || exp->inquote == 2)
			exp->inquote = check_solo_quote(&line[exp->i], exp->inquote);
		if (line[exp->i] == '$' && (exp->inquote == 0 || exp->inquote == 2))
			treat_dollar(exp, line, env);
		else if (line[exp->i] != '$' || (line[exp->i] == '$' && exp->inquote == 1))
			exp->i++;
	}
	if (exp->stop == -1)
		exp->newline = ft_strdup(line);
	else if (exp->stop != exp->i)
		get_back_buffer(exp, line);
	return (exp->newline);
}
