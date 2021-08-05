/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   without_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 13:32:44 by user42            #+#    #+#             */
/*   Updated: 2021/08/05 15:33:33 by user42           ###   ########.fr       */
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
