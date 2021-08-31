/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_array_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 20:57:56 by user42            #+#    #+#             */
/*   Updated: 2021/08/31 19:08:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_init(t_cmd *cmd)
{	
	cmd->arg = NULL;
	cmd->builtin = NULL;
	cmd->pipe = false;
	cmd->fdout = 1;
	cmd->fdin = 0;
}

int	do_beginning_bracket(int *i, const char *line, t_cmd *cmd, t_env_l *env)
{	
	int	start;

	start = 0;
	if (line[*i] == '<' && line[*i + 1] == '>')
	{
		*i = bracket_out_in(line, *i, cmd, env);
		start = *i;
	}
	if (line[*i] == '>')
	{
		*i = bracket_out(line, *i, cmd);
		start = *i;
	}
	else if (line[*i] == '<')
	{
		*i = bracket_in(line, *i, cmd, env);
		start = *i;
	}
	return (start);
}

static int	check_inquote_args(const char *line, int i, int *inquote)
{
	if (line[i] == '"' && check_end_quote(line + i) == 1)
	{
		i++;
		*inquote = 1;
	}
	else if (line [i] == '\'' && check_end_quote(line + i) == 1)
	{
		i++;
		*inquote = 2;
	}
	if (line [i] == '"' && *inquote == 1)
	{
		i++;
		*inquote = 0;
	}
	else if (line [i] == '\'' && *inquote == 2)
	{
		i++;
		*inquote = 0;
	}
	return (i);
}

int	pass_ascii(const char *line, int i)
{
	int		inquote;

	inquote = 0;
	while (ft_isascii(line[i]) == 1 || line[i] == ' ')
	{
		check_inquote_args(line, i, &inquote);
		if (line[i] == '|' && inquote == 0)
			break ;
		i++;
	}
	return (i);
}
