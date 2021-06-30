/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 21:02:14 by user42            #+#    #+#             */
/*   Updated: 2021/06/30 23:11:41 by user42           ###   ########.fr       */
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

char		*ft_strjoinzarb(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	i = 0;
	j = 0;
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1 + 1))))
		return (NULL);
	while (s1[i])
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	str[j] = ' ';
	j++;
	while (s2[i])
	{
		str[j] = s2[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

static const char	*fill_arg(const char *line, t_cmd *cmd)
{
	int		i;
	char	*args;

	i = 0;
	while (ft_isascii(line[i]) == 1 || line[i] == ' ')
	{
		if (line[i] == '|' || line[i] == ';')
			break ;
		i++;
	}
	args = ft_substr(line, 0, i);
	if (!args || ft_strlen(args) == 0)
	{
		cmd->arg = malloc(sizeof(char *) * 2);
		cmd->arg[0] = ft_strschr(cmd->builtin, '/');
		cmd->arg[1] = NULL;
	}
	else
		cmd->arg = ft_split(ft_strjoinzarb(cmd->builtin, args), ' ');
	i = 0;
	while ((size_t)i++ < ft_strlen(args))
		line++;
	free(args);
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
		if (*line++ == ';')
		{
			index++;
			continue ;
		}
		while (*line == ' ')
			line++;
		line = fill_arg(line, &cmd[index]);
		if (*line++ == '|')
			cmd[index].pipe = true;
		index++;
	}
}
