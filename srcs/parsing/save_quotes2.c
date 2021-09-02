/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_quotes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:22:55 by user42            #+#    #+#             */
/*   Updated: 2021/09/02 19:25:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_quote(char *expanded, int *i)
{
	char	c;

	if (expanded[*i] == '\'')
		c = '\'';
	else
		c = '"';
	while (expanded[*i] && expanded[*i] != c)
		i++;
	return (2);
}

int	is_quote_in(char *expanded)
{
	int	i;
	int	nb;
	int	inquote;

	i = 0;
	inquote = 0;
	nb = 0;
	while (expanded[i])
	{
		inquote = check_inquote(expanded[i], inquote);
		if (inquote == 1 || inquote == 2)
			inquote = check_solo_quote(&expanded[i], inquote);
		if (inquote == 1 && expanded[i] == '\'')
			nb = nb + count_quote(expanded, &i);
		else if (inquote == 2 && expanded[i] == '"')
			nb = nb + count_quote(expanded, &i);
		i++;
	}
	return (nb);
}

void	start_buffer(char *line, t_pars *qte)
{
	if (qte->stop == -1 && qte->i == 0)
		qte->newline = ft_strdup("");
	else if (qte->stop == -1 && qte->i > 0)
		qte->newline = ft_substr(line, 0, qte->i);
	qte->remember = qte->i;
	qte->i++;
}

void	get_saved_quote(char *line, t_pars *qte)
{
	while (line[qte->i] && line[qte->i] != '\'')
		qte->i++;
	if (line[qte->i] == '\'')
		qte->inquote = 0;
	qte->expanded = ft_substr(line, qte->remember, qte->i - qte->remember + 1);
	qte->tmp = ft_strjoin("\"", qte->expanded);
	free(qte->expanded);
	qte->expanded = ft_strjoin(qte->tmp, "\"");
	free(qte->tmp);
}
