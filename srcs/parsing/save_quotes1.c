/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_quotes1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:15:07 by user42            #+#    #+#             */
/*   Updated: 2021/09/02 19:25:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mid_buffer(char *line, t_pars *qte)
{
	if (qte->stop != -1 && qte->remember - qte->stop > 0)
	{
		qte->tmp = ft_strdup(qte->newline);
		free(qte->newline);
		qte->save = ft_substr(line, qte->stop, qte->remember - qte->stop);
		qte->newline = ft_strjoin(qte->tmp, qte->save);
		free(qte->save);
		free(qte->tmp);
	}
}

void	end_buffer(char *line, t_pars *qte)
{
	if (qte->stop == -1)
		qte->newline = ft_strdup(line);
	else if (qte->stop != qte->i)
	{
		qte->save = ft_substr(line, qte->stop, qte->i - qte->stop);
		qte->tmp = ft_strjoin(qte->newline, qte->save);
		free(line);
		free(qte->save);
		qte->newline = ft_strdup(qte->tmp);
		free(qte->tmp);
	}
}

void	add_quotes(char *line, t_pars *qte)
{
	start_buffer(line, qte);
	get_saved_quote(line, qte);
	mid_buffer(line, qte);
	qte->i++;
	qte->stop = qte->i;
	qte->tmp = ft_strdup(qte->newline);
	free(qte->newline);
	qte->newline = ft_strjoin(qte->tmp, qte->expanded);
	free(qte->tmp);
	free(qte->expanded);
}

char	*save_quotes(char *line)
{
	t_pars	qte;

	init_exp(&qte);
	while (line[qte.i])
	{
		qte.inquote = check_inquote(line[qte.i], qte.inquote);
		if (qte.inquote == 1 || qte.inquote == 2)
			qte.inquote = check_solo_quote(&line[qte.i], qte.inquote);
		if (line[qte.i] == '\'' && qte.inquote == 1)
			add_quotes(line, &qte);
		else
			qte.i++;
	}
	end_buffer(line, &qte);
	return (qte.newline);
}
