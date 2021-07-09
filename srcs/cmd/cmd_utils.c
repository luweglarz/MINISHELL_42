/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 20:59:56 by user42            #+#    #+#             */
/*   Updated: 2021/07/09 17:25:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_builtin(t_cmd cmd, char **env_list, bool pipe)
{
	int		len;

	len = ft_strlen(cmd.builtin);
	if (ft_strncmp(cmd.builtin, "echo", len) == 0 && cmd.error == false)
		builtin_echo(cmd, pipe);
	else if (ft_strncmp(cmd.builtin, "cd", len) == 0 && cmd.error == false)
		builtin_cd(cmd, pipe);
	else if (ft_strncmp(cmd.builtin, "pwd", len) == 0 && cmd.error == false)
		builtin_pwd(cmd, pipe);
	else if (ft_strncmp(cmd.builtin, "export", len) == 0 && cmd.error == false)
		builtin_export(cmd, env_list);
	else if (ft_strncmp(cmd.builtin, "unset", len) == 0 && cmd.error == false)
		builtin_unset(cmd, env_list);
	else if (ft_strncmp(cmd.builtin, "env", len) == 0 && cmd.error == false)
		builtin_env(cmd, env_list);
	else if (ft_strncmp(cmd.builtin, "exit", len) == 0 && cmd.error == false)
		builtin_exit(cmd);
	else
		execpath(cmd, env_list, pipe);
}

int	pass_redirections(const char *line, int j, int *start, int *append)
{
	if (line[j] == '>')
	{
		j++;
		if (line[j++] == '>' && append != NULL)
			*append = 1;
		while (line[j] == ' ')
			j++;
		if (start != NULL)
			*start = j;
		while ((ft_isascii(line[j]) == 1) && (line[j] != '|'
		|| line[j] != ';'))
			j++;
	}
	else if (line[j] == '<')
	{
		j++;
	 	while (line[j] == ' ')
	 		j++;
	 	if (start != NULL)
	 		*start = j;
	 	while ((ft_isascii(line[j]) == 1) && (line[j] != '|'
	 	|| line[j] != ';'))
	 		j++;		
	}
	return(j);
}

int	size_with_redirection(const char *line, int i)
{
	int j;
	int	k;
	int start;
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
	cmd->flows = NULL;
	cmd->error = false;
	cmd->pipe = false;
	cmd->fdout = 1;
	cmd->fdin = 0;
}
