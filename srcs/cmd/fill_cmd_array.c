/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:02:14 by user42            #+#    #+#             */
/*   Updated: 2021/07/16 15:18:47 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const char	*fill_builtin(const char *line, t_cmd *cmd)
{
	int		i;
	int		j;
	int 	start;

	i = 0;
	j = 0;
	start = 0;
	if (line[i] == '>')
	{
		i = bracket_out(line, &i, cmd);
		start = i;
	}
	else if (line[i] == '<')
	{
		i = bracket_in(line, &i, cmd);
		start = i;
	}
	while (ft_isascii(line[i]) == 1)
	{
		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			break ;
		i++;
	}
	cmd->builtin = ft_substr(line, start, i - start);
	while (j++ < i)
		line++;
	return (line);
}

static char	*formate_args(const char *line, t_cmd *cmd, int i)
{
	int		j;
	int		k;
	char	*newarg;

	j = 0;
	k = 0;
	newarg = malloc(sizeof(char) * (size_with_redirection(line, i) + 1));
	while (j < i)
	{	
		if (line[j] == '>')
			j = bracket_out(line, &j, cmd);
		else if (line[j] == '<')
			j = bracket_in(line, &j, cmd);
		newarg[k] = line[j];
		k++;
		j++;
	}
	newarg[k] = '\0';
	return (newarg);
}

static const char	*fill_arg(const char *line, t_cmd *cmd)
{
	int		i;
	int		j;
	int		inquote;
	char	*args;

	i = 0;
	inquote = 0;
	while (ft_isascii(line[i]) == 1 || line[i] == ' ')
	{
		if (line[i] == '"' && check_end_quote(line + i) == 1)
		{
			i++;
			inquote = 1;
		}
		else if (line [i] == '\'' && check_end_quote(line + i) == 1)
		{
			i++;
			inquote = 2;
		}
		if (line [i] == '"' && inquote == 1)
		{
			i++;
			inquote = 0;
		}
		else if (line [i] == '\'' && inquote == 2)
		{
			i++;
			inquote = 0;
		}
		if (line[i] == '|' && inquote == 0)
		{
			printf("la\n");
			break ;
		}
		i++;
	}
	args = formate_args(line, cmd, i);
	printf("les args %s\n", args);
	if (!args || ft_strlen(args) == 0)
	{
		cmd->arg = malloc(sizeof(char *) * 2);
		cmd->arg[0] = ft_strdup(cmd->builtin);
		cmd->arg[1] = NULL;
	}
	else
		cmd->arg = split_args(args, cmd->builtin);
	free(args);
	j = 0;
	while (j++ < i)
		line++;
	return (line);
}

void	fill_cmd_array(const char *line, t_cmd *cmd)
{
	int		index;

	index = 0;
	while (*line)
	{
		cmd_init(&cmd[index]);
		while (*line == ' ')
			line++;
		line = fill_builtin(line, &cmd[index]);
		while (*line == ' ')
			line++;
		line = fill_arg(line, &cmd[index]);
		if (*line == '|')
		{
			cmd[index].pipe = true;
			line++;
		}
		index++;
	}
	cmd_init(&cmd[index]);
}
