/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 18:25:19 by user42            #+#    #+#             */
/*   Updated: 2021/08/31 19:20:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	content_without_quote(char *expanded, int *i, int *res_index, char *res)
{
	char	c;

	c = expanded[*i];
	*i = *i + 1;
	while (expanded[*i] && expanded[*i] != c)
	{
		res[*res_index] = expanded[*i];
		*res_index = *res_index + 1;
		*i = *i + 1;
	}
}

void	format_quotes(char *expanded, char *res, int *res_index, int inquote)
{
	int	i;

	i = 0;
	while (expanded[i])
	{
		inquote = check_inquote(expanded[i], inquote);
		if (expanded[i] == '\'' || expanded[i] == '"')
			inquote = check_solo_quote(&expanded[i], inquote);
		if (expanded[i] == '\'' && inquote == 1)
		{
			content_without_quote(expanded, &i, res_index, res);
			update_inquote(expanded, &inquote, &i, '\'');
		}
		else if (expanded[i] == '"' && inquote == 2)
		{
			content_without_quote(expanded, &i, res_index, res);
			update_inquote(expanded, &inquote, &i, '"');
		}
		else
			fill_other_char(res, res_index, expanded, &i);
	}
}

char	*remove_quotes(char *expanded)
{
	int		res_index;
	int		i;
	char	*res;

	res_index = 0;
	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(expanded) - nb_quote(expanded) + 1));
	format_quotes(expanded, res, &res_index, 0);
	res[res_index] = '\0';
	return (res);
}
