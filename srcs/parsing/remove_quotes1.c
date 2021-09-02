/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:02:06 by user42            #+#    #+#             */
/*   Updated: 2021/09/02 19:05:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	treat_quotes(int i, int inquote, char *tmp, char *res)
{
	int	res_index;

	res_index = 0;
	while (tmp[i])
	{
		inquote = check_inquote(tmp[i], inquote);
		if (tmp[i] == '\'' || tmp[i] == '"')
			inquote = check_solo_quote(&tmp[i], inquote);
		if (tmp[i] == '\'' && inquote == 1)
		{
			get_quote_content(tmp, &i, &res_index, res);
			update_inquote(tmp, &inquote, &i, '\'');
		}
		else if (tmp[i] == '"' && inquote == 2)
		{
			get_quote_content(tmp, &i, &res_index, res);
			update_inquote(tmp, &inquote, &i, '"');
		}
		else
			fill_other_char(res, &res_index, tmp, &i);
	}
	res[res_index] = '\0';
}

char	*arg_without_quote(char *tmp, t_cmd *cmd, int ind, int ind2)
{
	char	*res;
	int		i;
	int		inquote;

	res = malloc(sizeof(char)
			* (ft_strlen(tmp) - quote_inside(cmd, ind, ind2) + 1));
	i = 0;
	inquote = 0;
	treat_quotes(i, inquote, tmp, res);
	return (res);
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
				if (j == 0)
					cmd[i].builtin = arg_without_quote(tmp, cmd, i, j);
				free(tmp);
			}
			j++;
		}
		i++;
	}
}
