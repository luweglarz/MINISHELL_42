/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:15:48 by lweglarz          #+#    #+#             */
/*   Updated: 2021/08/27 15:18:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	free_after_line(t_cmd *cmd, char *line)
{
	struct stat	*buf;
	char		*join;

	join = ft_strjoin(TMPDIR, ".heredoc");
	buf = malloc(sizeof(struct stat) * 1);
	if (stat(join, buf) == 0)
		unlink(join);
	free(buf);
	free(join);
	free_cmd(cmd);
	if (line)
	{
		free(line);
		line = NULL;
	}
}

char	*name_to_value(char *line, int *i, int inquote, char **env_list)
{
	int j;
	char *name;
	char *content;

	j = 0;
	while (line[j] && (ft_isalnum(line[j]) == 1 || line[j] == '_'))
		j++;
	if (j == 0)
		content = ft_strdup("");
	else
	{
		name = ft_substr(line, 0, j);
		content = ft_getenv(name, env_list);
		free(name);
		if (content == NULL)
			content = ft_strdup("");
	}
	*i = *i + j;
	return (content);
}

void	init_exp(t_pars *exp)
{
	exp->i = 0;
	exp->inquote = 0;
	exp->stop = -1;
	exp->remember = -1;
}

void	get_front_buffer(t_pars *exp, char *line)
{
	if (exp->stop == -1 && exp->i > 0)
		exp->newline = ft_substr(line, 0, exp->i);
	else if (exp->stop == -1 && exp->i == 0)
		exp->newline = ft_strdup("");
	exp->remember = exp->i;
	exp->i++;
}

void	get_median_buffer(t_pars *exp, char *line)
{
	exp->tmp = ft_strdup(exp->newline);
	free(exp->newline);
	exp->save = ft_substr(line, exp->stop, exp->remember - exp->stop);
	exp->newline = ft_strjoin(exp->tmp, exp->save);
	free(exp->save);
	free(exp->tmp);
}

void	get_back_buffer(t_pars *exp, char *line)
{
	exp->tmp = ft_strdup(exp->newline);
	free(exp->newline);
	exp->save = ft_substr(line, exp->stop, exp->i - exp->stop);
	exp->newline = ft_strjoin(exp->tmp, exp->save);
	free(exp->tmp);
	free(exp->save);
}

char	*expand_env_value(char *line, char **env_list)
{
	t_pars exp;

	init_exp(&exp);
	/*exp.i = 0;
	exp.inquote = 0;
	exp.stop = -1;
	exp.remember = -1;*/
	while (line[exp.i])
	{
		exp.inquote = check_inquote(line[exp.i], exp.inquote);
		if (exp.inquote == 1 || exp.inquote == 2)
			exp.inquote = check_solo_quote(&line[exp.i], exp.inquote);
		if (line[exp.i] == '$' && (exp.inquote == 0 || exp.inquote == 2))
		{
			if (line[exp.i] && (ft_isalnum(line[exp.i + 1]) != 1 && line[exp.i + 1] != '_' && line[exp.i + 1] != '?'))
				exp.i++;
			else if (line[exp.i] && (ft_isalnum(line[exp.i + 1]) == 1 || line[exp.i + 1] == '_' || line[exp.i + 1] == '?'))
			{
				get_front_buffer(&exp, line);
				/*if (exp.stop == -1 && exp.i > 0)
					exp.newline = ft_substr(line, 0, exp.i);
				else if (exp.stop == -1 && exp.i == 0)
					exp.newline = ft_strdup("");
				exp.remember = exp.i;
				exp.i++;*/
				if (line[exp.i] == '?')
				{
					exp.i++;
					exp.expanded = ft_itoa(g_err);
				}
				else
					exp.expanded = name_to_value(&line[exp.i], &exp.i, exp.inquote, env_list);
				if (exp.expanded != NULL)
				{
					if (exp.stop != -1 && exp.remember - exp.stop > 0)
					{
						get_median_buffer(&exp, line);
						/*exp.tmp = ft_strdup(exp.newline);
						free(exp.newline);
						exp.save = ft_substr(line, exp.stop, exp.remember - exp.stop);
						exp.newline = ft_strjoin(exp.tmp, exp.save);
						free(exp.save);
						free(exp.tmp);*/
					}
					exp.stop = exp.i;
					exp.tmp = ft_strdup(exp.newline);
					free(exp.newline);
					exp.newline = ft_strjoin(exp.tmp, exp.expanded);
					free(exp.tmp);
					free(exp.expanded);
				}
			}
		}
		else if (line[exp.i] != '$' || (line[exp.i] == '$' && exp.inquote == 1))
			exp.i++;
	}
	if (exp.stop == -1)
		exp.newline = ft_strdup(line);
	else if (exp.stop != exp.i)
	{
		get_back_buffer(&exp, line);
		/*exp.tmp = ft_strdup(exp.newline);
		free(exp.newline);
		exp.save = ft_substr(line, exp.stop, exp.i - exp.stop);
		exp.newline = ft_strjoin(exp.tmp, exp.save);
		free(exp.tmp);
		free(exp.save);*/
	}
	return (exp.newline);
}

void	treat_cmd(t_cmd *cmd, int nb_cmd, t_env_l *env, char *line)
{
	char *expanded;

	cmd = malloc(sizeof(t_cmd) * (nb_cmd + 1));
	expanded = expand_env_value(line, env->list);
	fill_cmd_array(expanded, cmd);
	free(expanded);
	del_quotes(cmd, nb_cmd);
	parse_cmd_array(cmd, env, nb_cmd);
	free_after_line(cmd, line);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	t_env_l	env;
	int		nb_cmd;

	cmd = NULL;
	env.list = init_env(envp, ac, av);
	signal(SIGINT, sig_handler);
	nb_cmd = 0;
	line = NULL;
	while (1)
	{
		line = readline("Minishell>");
		if (line)
			add_history(line);
		if (line == NULL)
			exit(0);
		nb_cmd = parse_command(line);
		if (nb_cmd >= 0)
			treat_cmd(cmd, nb_cmd, &env, line);
		else
			free_after_line(cmd, line);
	}
	return (1);
}
