/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:02:14 by user42            #+#    #+#             */
/*   Updated: 2021/09/29 12:08:46 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const char	*fill_builtin(const char *line, t_cmd *cmd, t_env_l *env)
{
	int		i;
	int		j;
	int		start;

	j = 0;
	i = 0;
	start = do_beginning_bracket(&i, line, cmd, env);
	if (start != 0)
		i = start + 1;
	while (ft_isascii(line[i]) == 1)
	{
		if ((line[i] == '|' || line[i] == '<'
				|| line[i] == '>') && (start == 0))
			break ;
		i++;
	}
	if (start != 0)
		start++;
	cmd->builtin = ft_substr(line, start, i - start);
	while (j++ < i)
		line++;
	return (line);
}

static int	fill_newarg(const char *line, char *newarg, int *j, int inquote)
{
	static int	k;

	if (!k)
		k = 0;
	if (newarg == NULL)
	{
		k = 0;
		return (0);
	}
	if ((line[*j] != '<' && line[*j] != '>' && inquote == 0) || (inquote == 1)
		|| (inquote == 2))
	{
		newarg[k] = line[*j];
		k++;
		*j = *j + 1;
	}
	return (k);
}

static char	*formate_args(const char *line, t_cmd *cmd, int i, t_env_l *env)
{
	int		j;
	int		k;
	int		inquote;
	char	*newarg;

	j = 0;
	k = 0;
	inquote = 0;
	newarg = malloc(sizeof(char) * (formate_args_size(line, i)));
	while (j < i)
	{	
		check_inquote_args(line, j, &inquote);
		if (line[j] == '<' && line[j + 1] == '>' && inquote == 0)
			j = bracket_out_in(line, j, cmd, env);
		if (line[j] == '>' && inquote == 0)
			j = bracket_out(line, j, cmd);
		else if (line[j] == '<' && inquote == 0)
			j = bracket_in(line, j, cmd, env);
		k = fill_newarg(line, newarg, &j, inquote);
	}
	newarg[k] = '\0';
	fill_newarg(line, NULL, &j, inquote);
	return (newarg);
}

static const char	*fill_arg(const char *line, t_cmd *cmd, t_env_l *env)
{
	int		i;
	int		j;
	char	*args;

	i = 0;
	i = pass_ascii(line, i);
	args = formate_args(line, cmd, i, env);
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

void	fill_cmd_array(const char *line, t_cmd *cmd, t_env_l *env)
{
	int		index;

	index = 0;
	while (*line)
	{
		cmd_init(&cmd[index]);
		while (*line == ' ')
			line++;
		line = fill_builtin(line, &cmd[index], env);
		while (*line == ' ')
			line++;
		line = fill_arg(line, &cmd[index], env);
		if (*line == '|')
		{
			cmd[index].pipe = true;
			line++;
		}
		index++;
	}
	cmd_init(&cmd[index]);
}
