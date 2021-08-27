/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 15:58:17 by user42            #+#    #+#             */
/*   Updated: 2021/08/27 16:03:55 by user42           ###   ########.fr       */
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

void	treat_dollar(t_pars *exp, char *line, char **env_list)
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
		else
			exp->expanded = name_to_value(&line[exp->i], &exp->i, env_list);
		if (exp->expanded != NULL)
			add_expanded(exp, line);
	}
}

char	*expand_env_value(char *line, char **env_list)
{
	t_pars	exp;

	init_exp(&exp);
	while (line[exp.i])
	{
		exp.inquote = check_inquote(line[exp.i], exp.inquote);
		if (exp.inquote == 1 || exp.inquote == 2)
			exp.inquote = check_solo_quote(&line[exp.i], exp.inquote);
		if (line[exp.i] == '$' && (exp.inquote == 0 || exp.inquote == 2))
			treat_dollar(&exp, line, env_list);
		else if (line[exp.i] != '$' || (line[exp.i] == '$' && exp.inquote == 1))
			exp.i++;
	}
	if (exp.stop == -1)
		exp.newline = ft_strdup(line);
	else if (exp.stop != exp.i)
		get_back_buffer(&exp, line);
	return (exp.newline);
}
