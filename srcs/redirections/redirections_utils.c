/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 21:10:37 by user42            #+#    #+#             */
/*   Updated: 2021/09/27 19:06:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int
	pass_right_bracket(const char *line, int j, int *start, int *doublebracket)
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
	{
		if (line[j] == '>' || line[j] == '<')
			return (j);
		j++;
	}
	return (j);
}

static int
	pass_left_bracket(const char *line, int j, int *start, int *doublebracket)
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
	{
		if (line[j] == '>' || line[j] == '<')
			return (j);
		j++;
	}
	return (j);
}

int	pass_brackets(const char *line, int j, int *start, int *doublebracket)
{
	if (line[j] == '>')
		j = pass_right_bracket(line, j, start, doublebracket);
	else if (line[j] == '<')
		j = pass_left_bracket(line, j, start, doublebracket);
	return (j);
}

int	size_with_redirection(const char *line, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j < i)
	{	
		if (line[j] == '>' || line[j] == '<')
			j = pass_brackets(line, j, NULL, NULL);
		k++;
		j++;
	}
	return (k);
}

int	wait_forks(pid_t *pid, int nb_pipe)
{
	int	i;

	i = 0;
	while (i++ < nb_pipe)
		waitpid(pid[i], NULL, 0);
	free(pid);
	return (i);
}
