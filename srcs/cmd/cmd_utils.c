/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:59:56 by user42            #+#    #+#             */
/*   Updated: 2021/07/14 15:15:47 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_builtin(t_cmd cmd, char **env_list, bool pipe)
{
	int		len;

	if (cmd.fdin == -1)
		return ;
	len = ft_strlen(cmd.builtin);
	if (ft_strncmp(cmd.builtin, "echo", len + 1) == 0)
		builtin_echo(cmd, pipe);
	else if (ft_strncmp(cmd.builtin, "cd", len + 1) == 0)
		builtin_cd(cmd, pipe);
	else if (ft_strncmp(cmd.builtin, "pwd", len + 1) == 0)
		builtin_pwd(cmd, pipe);
	else if (ft_strncmp(cmd.builtin, "export", len + 1) == 0)
		builtin_export(cmd, env_list);
	else if (ft_strncmp(cmd.builtin, "unset", len + 1) == 0)
		builtin_unset(cmd, env_list);
	else if (ft_strncmp(cmd.builtin, "env", len + 1) == 0)
		builtin_env(cmd, env_list);
	else if (ft_strncmp(cmd.builtin, "exit", len + 1) == 0)
		builtin_exit(cmd);
	else
		execpath(cmd, env_list, pipe);
}

int	pass_redirections(const char *line, int j, int *start, int *doublebracket)
{
	if (line[j] == '>')
	{
		j++;
		if (line[j + 1] == '>' && doublebracket != NULL)
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
		if (line[j + 1] == '<' && doublebracket != NULL)
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
