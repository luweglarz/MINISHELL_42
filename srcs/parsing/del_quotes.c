/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 04:16:57 by user42            #+#    #+#             */
/*   Updated: 2021/08/05 13:32:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	while (cmd[i].arg[j][index])
	{
		inquote = check_inquote(cmd[i].arg[j][index], inquote);
		if (cmd[i].arg[j][index] == '\'' || cmd[i].arg[j][index] == '"')
			inquote = check_solo_quote(&cmd[i].arg[j][index], inquote);
		if (cmd[i].arg[j][index] == '\'' && inquote == 1)
			nb = nb + increment_quote(cmd, i, j, &index);
		else if (cmd[i].arg[j][index] == '"' && inquote == 2)
			nb = nb + increment_quote(cmd, i, j, &index);
		index++;
	}
	return (nb);
}

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

void	del_quotes(t_cmd *cmd, int nb_cmd)
{
	int		i;
	int		j;
	int		quote;
	char	*tmp;

	i = 0;
	while (i < nb_cmd)
	{
		j = 0;
		while (cmd[i].arg[j])
		{
			quote = quote_inside(cmd, i, j);
			if (quote > 0)
			{
				tmp = ft_strdup(cmd[i].arg[j]);
				free(cmd[i].arg[j]);
				cmd[i].arg[j] = arg_without_quote(tmp, cmd, i, j);
			}
			j++;
		}
		i++;
	}
}
