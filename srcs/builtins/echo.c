/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 16:17:20 by user42            #+#    #+#             */
/*   Updated: 2021/08/23 21:21:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_option_str(char *arg)
{
	int	j;

	j = 0;
	if (arg[j++] != '-')
		return (1);
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (1);
		j++;
	}
	return (0);
}

static int	check_option_first(char *arg)
{
	int	i;

	i = 0;
	if (arg[i++] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	check_option(char **arg, int *i)
{
	int	option;
	int	do_break;

	option = 0;
	do_break = 0;
	if (arg == NULL)
		return (-1);
	option = check_option_first(arg[*i]);
	while (arg[*i])
	{
		do_break = check_option_str(arg[*i]);
		if (do_break == 1)
			break ;
		*i = *i + 1;
	}
	return (option);
}

static void	display_echo(t_cmd cmd)
{
	int	i;

	i = 1;
	if (check_option(cmd.arg, &i) == 1)
	{
		while (cmd.arg[i])
		{
			write(cmd.fdout, cmd.arg[i], ft_strlen(cmd.arg[i]));
			if (cmd.arg[i + 1])
				write(cmd.fdout, " ", 1);
			i++;
		}
	}
	else
	{
		while (cmd.arg[i] != NULL)
		{
			write(cmd.fdout, cmd.arg[i], ft_strlen(cmd.arg[i]));
			if (cmd.arg[i + 1])
				write(cmd.fdout, " ", 1);
			i++;
		}
		write(cmd.fdout, "\n", 1);
	}
}

void	builtin_echo(int i, t_cmd *cmd, bool pipe)
{
	g_err = 0;
	if (pipe == false)
	{
		if (cmd[i].arg[1] == NULL)
		{
			write(cmd->fdout, "\n", 1);
			return ;
		}
		display_echo(cmd[i]);
	}
	else if (pipe == true)
	{
		if (cmd[i].arg[1] == NULL)
		{
			write(cmd->fdout, "\n", 1);
			exit(1);
		}
		display_echo(cmd[i]);
		exit(1);
	}
}
