/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:02:14 by user42            #+#    #+#             */
/*   Updated: 2021/07/09 23:25:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const char	*fill_builtin(const char *line, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (ft_isascii(line[i]) == 1)
		i++;
	cmd->builtin = ft_substr(line, 0, i);
	i = 0;
	while ((size_t)i++ < ft_strlen(cmd->builtin))
		line++;
	return (line);
}

int	create_redirection_files(const char *line, int *j, t_cmd *cmd)
{
	char	*file;
	int		start;
	int		append;
	struct stat buf;

	start = 0;
	append = 0;
	file = NULL;
	if (line[*j] == '>')
	{
		*j = pass_redirections(line, *j, &start, &append);
		file = ft_substr(line, start, *j - start);
		if (append == 1)
			cmd->fdout = open(file, O_RDWR|O_APPEND|O_CREAT, 0664);
		else
			cmd->fdout = open(file, O_RDWR|O_CREAT, 0664);
	}
	else if (line[*j] == '<')
	{
		*j = pass_redirections(line, *j, &start, &append);
		file = ft_substr(line, start, *j - start);
		if (stat(file, &buf) == - 1)
		{
			write(2, strerror(errno), ft_strlen(strerror(errno)));
			write(2, "\n", 1);
		}
		else
			cmd->fdin = open(file, O_RDWR);
	}
	if (file)
		free(file); 
	return (*j);
}

static char	*formate_args(const char *line, t_cmd *cmd, int i)
{
	int 	j;
	int		k;
	char	*newarg;

	j = 0;
	k = 0;
	newarg = malloc(sizeof(char) * (size_with_redirection(line, i) + 1));
	while (j < i)
	{	
		j = create_redirection_files(line, &j, cmd);
		newarg[k] = line[j];
		k++;
		j++;
	}
	newarg[k] = '\0';
	printf("le newargs %s\n", newarg);
	return (newarg);
}

static const char	*fill_arg(const char *line, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*args;

	i = 0;
	while (ft_isascii(line[i]) == 1 || line[i] == ' ')
	{
		if (line[i] == '|' || line[i] == ';')
			break ;
		i++;
	}
	args = formate_args(line, cmd, i);
	printf("le newarg %s\n", args);
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
		else if (*line == ';')
		{
			line++;
			index++;
			continue;
		}
		index++;
	}
	cmd_init(&cmd[index]);
}