/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:02:14 by user42            #+#    #+#             */
/*   Updated: 2021/07/08 18:55:29 by user42           ###   ########.fr       */
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

int	pass_flows(const char *line, int j, int *start)
{
	int	append;

	append = 0;
	if (line[j] == '>')
	{
		j++;
		if (line[j++] == '>')
			append = 1;
		while (line[j] == ' ')
			j++;
		*start = j;
		while ((ft_isascii(line[j]) == 1) && (line[j] != '|'
		|| line[j] != ';'))
			j++;
	}
	else if (line[j] == '<')
	{
		j++;
		if (line[j++] == '<')
			append = 1;
		while (line[j] == ' ')
			j++;
		*start = j;
		while ((ft_isascii(line[j]) == 1) && (line[j] != '|'
		|| line[j] != ';'))
			j++;		
	}
	return(j);
}

int	dosize(const char *line, int i)
{
	int j;
	int	k;
	int start;

	j = 0;
	k = 0;
	start = 0;
	while (j < i)
	{	
		if (line[j] == '>' || line[j] == '<')
			j = pass_flows(line, j, &start);
		k++;
		j++;
	}
	printf("le k tqt %d\n", k);
	return (k);
}

char	*formate_args(const char *line, t_cmd *cmd, int i)
{
	int 	j;
	int		k;
	int		start;
	char	*newarg;

	j = 0;
	k = 0;
	start = 0;
	newarg = malloc(sizeof(char) * (dosize(line, i) + 1));
	while (j < i)
	{	
		if (line[j] == '>' || line[j] == '<')
		{
			j = pass_flows(line, j, &start);
			cmd->fd = open(ft_substr(line, start, j - start), O_RDWR|O_CREAT, 0664);
		}
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
	//	line = check_flows(line, &cmd[index]);
		line = fill_arg(line, &cmd[index]);
		printf("les args 1 %s\n", cmd[index].arg[0]);
		printf("les args 2 %s\n", cmd[index].arg[1]);
		printf("les args 3 %s\n", cmd[index].arg[2]);
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