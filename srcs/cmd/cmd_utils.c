/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:59:56 by user42            #+#    #+#             */
/*   Updated: 2021/07/22 16:42:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_builtin(int i, t_cmd *cmd, char **env_list, bool pipe)
{
	int		len;

	if (cmd[i].fdin == -1)
		return ;
	len = ft_strlen(cmd[i].builtin);
	if (ft_strncmp(cmd[i].builtin, "echo", len + 1) == 0)
		builtin_echo(i, cmd, pipe);
	else if (ft_strncmp(cmd[i].builtin, "cd", len + 1) == 0)
		builtin_cd(i, cmd, pipe);
	else if (ft_strncmp(cmd[i].builtin, "pwd", len + 1) == 0)
		builtin_pwd(i, cmd, pipe);
	else if (ft_strncmp(cmd[i].builtin, "export", len + 1) == 0)
		builtin_export(i, cmd, env_list);
	else if (ft_strncmp(cmd[i].builtin, "unset", len + 1) == 0)
		builtin_unset(i, cmd, env_list);
	else if (ft_strncmp(cmd[i].builtin, "env", len + 1) == 0)
		builtin_env(i, cmd, env_list);
	else if (ft_strncmp(cmd[i].builtin, "exit", len + 1) == 0)
		builtin_exit(i, cmd);
	else
		execpath(i, cmd, env_list, pipe);
}

int	pass_redirections(const char *line, int j, int *start, int *doublebracket)
{
	if (line[j] == '>')
	{
		j++;
		if (line[j] == '>' && doublebracket != NULL)
		{
			j++;
			*doublebracket = 1;
		}
		while (line[j] == ' ')
			j++;
		if (start != NULL)
			*start = j;
		while ((ft_isascii(line[j]) == 1) && line[j] != '|')
			j++;
	}
	else if (line[j] == '<')
	{
		j++;
		if (line[j] == '<' && doublebracket != NULL)
		{
			j++;
			*doublebracket = 1;
		}
		while (line[j] == ' ')
			j++;
		if (start != NULL)
			*start = j;
		while ((ft_isascii(line[j]) == 1) && line[j] != '|')
			j++;
	}
	return (j);
}

int	size_with_redirection(const char *line, int i)
{
	int	j;
	int	k;
	int	start;
	int	append;

	j = 0;
	k = 0;
	start = 0;
	append = 0;
	while (j < i)
	{	
		if (line[j] == '>' || line[j] == '<')
			j = pass_redirections(line, j, NULL, NULL);
		k++;
		j++;
	}
	return (k);
}

void	cmd_init(t_cmd *cmd)
{	
	cmd->arg = NULL;
	cmd->builtin = NULL;
	cmd->pipe = false;
	cmd->fdout = 1;
	cmd->fdin = 0;
}
