/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:15:48 by lweglarz          #+#    #+#             */
/*   Updated: 2021/06/14 15:27:03 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


int	ft_isascii(int c)
{
	if (c > 0 && c <= 127)
		return (1);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (s[start] && i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char    *get_line()
{
    char *line;

    line = NULL;
    if (line)
    {
        free(line);
        line = NULL;
    }
    line = readline("Minishell>");
    if (line)
        add_history(line);
    return (line);
}

void	cmd_init(t_cmd *cmd)
{
	cmd->arg = NULL;
	cmd->builtin = NULL;
	cmd->option = NULL;
	cmd->error = NULL;
	cmd->cmd_index = 0;
}

void	do_builtin(const char *builtin)
{
	if (ft_strncmp(builtin, "echo", 4) == 0)
		builtin_echo(1);
	else if (ft_strncmp(builtin, "cd", 4) == 0)
		builtin_echo(1);
	else if (ft_strncmp(builtin, "pwd", 3) == 0)
		builtin_echo(1);
	else if (ft_strncmp(builtin, "export", 6) == 0)
		builtin_echo(1);
	else if (ft_strncmp(builtin, "unset", 5) == 0)
		builtin_echo(1);
	else if (ft_strncmp(builtin, "env", 3) == 0)
		builtin_echo(1);
}

char    *fill_builtin(const char *line)
{
    int     i;
    char    *ret;

    i = 0;
    while (ft_isascii(line[i]) == 1)
        i++;
    ret = malloc(sizeof(char) * i + 1);
    if (!ret)
        return (NULL);
    ret = ft_substr(line, 0, i);
    return (ret);
}

void	fill_cmd_array(const char *line, t_cmd *cmd)
{
	int	size;
	int	index;

    index = 0;
	while (*line)
	{
        printf("index %d\n", index);
        cmd_init(&cmd[index]);
		while (*line == ' ')
			line++;
		cmd[index].builtin = fill_builtin(line);
        printf("builtin dans la func %s\n", cmd[index].builtin);
        if (cmd[index].builtin)
		    size = ft_strlen(cmd[index].builtin);
		while (size--)
			line++;
		while (*line == ' ')
			line++;
		cmd[index].cmd_index = index;
		index++;
		line++;
	}	
}

int main(void)
{
	t_cmd 	*cmd;
    char 	*line;

	cmd = NULL;
    while (1)
	{
        line = get_line();
		cmd = parse_command(line);
		fill_cmd_array(line, cmd);
        printf("%s\n", cmd[0].builtin);
		if (cmd)
			free(cmd);
	}
}
