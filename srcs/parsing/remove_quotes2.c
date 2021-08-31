/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 18:25:32 by user42            #+#    #+#             */
/*   Updated: 2021/08/31 18:27:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_other_char(char *res, int *res_index, char *tmp, int *i)
{
	res[*res_index] = tmp[*i];
	*res_index = *res_index + 1;
	*i = *i + 1;
}

void	update_inquote(char *tmp, int *inquote, int *i, char c)
{
	if (tmp[*i] == c)
		*inquote = check_inquote(tmp[*i], *inquote);
	*i = *i + 1;
}

int	increment_nbquote(char *expanded, int *i)
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

int	nb_quote(char *expanded)
{
	int	i;
	int	inquote;
	int	nb;

	i = 0;
	nb = 0;
	inquote = 0;
	while (expanded[i])
	{
		inquote = check_inquote(expanded[i], inquote);
		if (expanded[i] == '\'' || expanded[i] == '"')
			inquote = check_solo_quote(&expanded[i], inquote);
		if (expanded[i] == '\'' && inquote == 1)
			nb = nb + increment_nbquote(expanded, &i);
		else if (expanded[i] == '"' && inquote == 2)
			nb = nb + increment_nbquote(expanded, &i);
		i++;
	}
	return (nb);
}
