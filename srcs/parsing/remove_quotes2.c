/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:05:29 by user42            #+#    #+#             */
/*   Updated: 2021/09/02 19:05:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_quote_content(char *tmp, int *i, int *res_index, char *res)
{
	char	c;

	c = tmp[*i];
	*i = *i + 1;
	while (tmp[*i] && tmp[*i] != c)
	{
		res[*res_index] = tmp[*i];
		*res_index = *res_index + 1;
		*i = *i + 1;
	}
}

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

int	increment_quote(t_cmd *cmd, int i, int j, int *index)
{
	char	c;

	if (cmd[i].arg[j][*index] == '\'')
		c = '\'';
	else
		c = '"';
	while (cmd[i].arg[j][*index] && cmd[i].arg[j][*index] != c)
		index++;
	return (2);
}

int	quote_inside(t_cmd *cmd, int i, int j)
{
	int	index;
	int	inquote;
	int	nb;

	index = 0;
	nb = 0;
	inquote = 0;
	while (index < (int)ft_strlen(cmd[i].arg[j]))
	{
		inquote = check_inquote(cmd[i].arg[j][index], inquote);
		if (cmd[i].arg[j][index] == '\'' || cmd[i].arg[j][index] == '"')
			inquote = check_solo_quote(&cmd[i].arg[j][index], inquote);
		if (cmd[i].arg[j][index] == '\'' && inquote == 1)
			nb = nb + increment_quote(cmd, i, j, &index);
		else if (cmd[i].arg[j][index] == '"' && inquote == 2)
			nb = nb + increment_quote(cmd, i, j, &index);
		if (index != (int)ft_strlen(cmd[i].arg[j]))
			index++;
	}
	return (nb);
}
