/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 19:10:58 by user42            #+#    #+#             */
/*   Updated: 2021/08/31 19:11:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
