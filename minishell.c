/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:15:48 by lweglarz          #+#    #+#             */
/*   Updated: 2021/07/16 01:51:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*get_line(const char *prompt)
{
	char	*line;

	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline(prompt);
	if (line)
		add_history(line);
	return (line);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == EOF)
		exit(1);
}

void	free_after_line(t_cmd *cmd, char *line)
{
	struct stat	*buf;
	//char		*join;

	buf = malloc(sizeof(struct stat) * 1);
	//join = ft_strjoin(getenv("TMPDIR"), ".heredoc");
	//if (stat(join, buf) == 0)
	//	unlink(join);
	//free(join);
	free(buf);
	free_cmd(cmd);
	if (line)
	{
		free(line);
		line = NULL;
	}
}

int		dollar_inside(t_cmd *cmd, int i, int j)
{
	int index;
	int nb;

	nb = 0;
	index = 0;
	while (cmd[i].arg[j][index])
	{
		if (cmd[i].arg[j][index] == '$')
			nb++;
		index++;
	}
	return (nb);
}

int		check_solo_quote(char *arg, int inquote)
{
	int i;

	i = 0;
	if (arg[i] == '\'')
	{
		i++;
		while (arg[i])
		{
			if (arg[i] == '\'')
				return (inquote);
			i++;
		}
		inquote = 0;
		return (inquote);
	}
	else if (arg[i] == '"')
	{
		i++;
		while (arg[i])
		{
			if (arg[i] == '"')
				return (inquote);
			i++;
		}
		inquote = 0;
		return (inquote);
	}
	else
		return (inquote);
}

char	*ft_getenv_quoted(char *var_name, char **env_list)
{
	char *str;
	char *res;
	char *tmp;
	char **tab;
	int i;

	i = 0;
	str = ft_getenv(var_name, env_list);
	res = NULL;
	if (str == NULL)
		return (NULL);
	else
	{
		tab = ft_split(str, ' ', NULL);
		free(str);
		tmp = ft_strdup(tab[i]);
		i++;
		while (tab[i] && i > 0)
		{
			if (i == 1)
				str = ft_strdup(" ");
			else
			{
				str = ft_strdup(" ");
				tmp = ft_strjoin(res, str);
			}
			res = ft_strjoin(tmp, str);
			free(str);
			free(tmp);
			i++;
		}
		if (res == NULL)
			res = ft_strdup(tmp);
		return (res);
	}
}

void	expand_env_arg(t_cmd *cmd, char **env_list, int i, int j)
{
	t_pars pars;

	//init_pars_struct(pars);
	pars.var_content = NULL;
	pars.var_name = NULL;
	pars.tmp = NULL;
	pars.res = NULL;
	pars.index = 0;
	pars.stop = -1;
	pars.inquote = 0;
	while (cmd[i].arg[j][pars.index])
	{
		pars.inquote = check_inquote(cmd[i].arg[j][pars.index], pars.inquote);
		if (pars.inquote == 1 || pars.inquote == 2)
			pars.inquote = check_solo_quote(&cmd[i].arg[j][pars.index], pars.inquote);
		//printf("[DEBUG1] inquote = %d | stop = %d - %s| &cmd[i].arg[j] = %s\n", pars.inquote, pars.stop, &cmd[i].arg[j][pars.stop], &cmd[i].arg[j][pars.index]);
		if (cmd[i].arg[j][pars.index] == '$' && (pars.inquote == 0 || pars.inquote == 2))
		{
			//Je recupere ce qui est avant le $
			if (pars.stop == -1)
				pars.tmp = ft_substr(cmd[i].arg[j], 0, pars.index);
			else if (pars.res != NULL)
			{
				if (pars.stop != pars.index)
				{
					pars.var_content = ft_substr(cmd[i].arg[j], pars.stop, pars.index - pars.stop);
					pars.tmp = ft_strjoin(pars.res, pars.var_content);
					//printf("[DEBUG] res = %s\n", pars.res);
					//printf("[DEBUG] var_content = %s\n", pars.var_content);
					free(pars.var_content);
					free(pars.res);
					pars.res = NULL;
				}
				else
				{
					pars.tmp = ft_strdup(pars.res);
					free(pars.res);
					pars.res = NULL;
				}
			}
			pars.index++;
			pars.stop = pars.index;
			//
			if (cmd[i].arg[j][pars.index] == '\0' || cmd[i].arg[j][pars.index] == '\'' || cmd[i].arg[j][pars.index] == '"')
			{
				pars.var_content = ft_strdup("$");
				if (cmd[i].arg[j][pars.index] == '\'')
					pars.inquote = 1;
				else if (cmd[i].arg[j][pars.index] == '"' && pars.inquote == 2)
					pars.inquote = 0;
				else if (cmd[i].arg[j][pars.index] == '"' && pars.inquote == 0)
					pars.inquote = 2;
			}
			else if (cmd[i].arg[j][pars.index] == '?')
				pars.var_content = ft_strdup("1");
			else
			{
				while (cmd[i].arg[j][pars.index] && cmd[i].arg[j][pars.index] != '$' && cmd[i].arg[j][pars.index] != '\'' && cmd[i].arg[j][pars.index] != '"')
					pars.index++;
				//Je recupere ce qui est apres le $
				pars.var_name = ft_substr(cmd[i].arg[j], pars.stop, pars.index - pars.stop);
				if (pars.inquote == 0)
					pars.var_content = ft_getenv(pars.var_name, env_list);
				else if (pars.inquote == 2)
					pars.var_content = ft_getenv_quoted(pars.var_name, env_list);
				pars.stop = pars.index;
				if (cmd[i].arg[j][pars.index] == '\'' || cmd[i].arg[j][pars.index] == '"')
					pars.index--;
				if (pars.var_content == NULL)
					pars.var_content = ft_strdup("");
				free(pars.var_name);
				pars.var_name = NULL;
			}
			printf("[DEBUG2] inquote = %d | stop = %d | &cmd[i].arg[j] = %s\n", pars.inquote, pars.stop, &cmd[i].arg[j][pars.index]);
			//Je join ou dup les morceaux de l'argument
			if (pars.tmp)
			{
				pars.res = ft_strjoin(pars.tmp, pars.var_content);
				free(pars.tmp);
				pars.tmp = NULL;
			}
			else
				pars.res = ft_strdup(pars.var_content);
			free(pars.var_content);
			pars.var_content = NULL;
		}
		if (cmd[i].arg[j][pars.index] != '$' || (cmd[i].arg[j][pars.index] == '$' && pars.inquote == 1))
			pars.index++;
	}
	if (pars.tmp == NULL)
	{
		pars.tmp = ft_substr(cmd[i].arg[j], pars.stop, ft_strlen(cmd[i].arg[j]));
		pars.var_content = ft_strjoin(pars.res, pars.tmp);
		free(pars.tmp);
		free(pars.res);
		pars.res = ft_strdup(pars.var_content);
		free(pars.var_content);
	}
	if (pars.res != NULL)
	{
		free(cmd[i].arg[j]);
		cmd[i].arg[j] = ft_strdup(pars.res);
		free(pars.res);
		pars.res = NULL;
	}
}

void	format_args(t_cmd *cmd, char **env_list, int nb_cmd)
{
	int i;
	int j;
	int dollar;

	i = 0;
	while (i < nb_cmd)
	{
		j = 0;
		while (cmd[i].arg[j])
		{
			dollar = dollar_inside(cmd, i, j);
			printf("ARG[%d] = %s\n", j, cmd[i].arg[j]);
			if (dollar > 0)
				expand_env_arg(cmd, env_list, i, j);
			j++;
		}
		i++;
	}
}

int		quote_inside(t_cmd *cmd, int i, int j)
{
	int index;
	int inquote;
	int nb;

	index = 0;
	nb = 0;
	while (cmd[i].arg[j][index])
	{
		inquote = check_inquote(cmd[i].arg[j][index], inquote);
		if (inquote == 1 || inquote == 2)
			inquote = check_solo_quote(&cmd[i].arg[j][index], inquote);
		if (inquote == 1)
		{
			nb = nb + 2;
			while (cmd[i].arg[j][index] && inquote == 1)
			{
				inquote = check_inquote(cmd[i].arg[j][index], inquote);
				index++;
			}
		}
		else if (inquote == 2)
		{
			nb = nb + 2;
			while (cmd[i].arg[j][index] && inquote == 2)
			{
				inquote = check_inquote(cmd[i].arg[j][index], inquote);
				index++;
			}
		}
		index++;
	}
	return (nb);
}

void	del_quotes(t_cmd *cmd, char **env_list, int nb_cmd)
{
	int i;
	int j;
	int quote;

	i = 0;
	while (i < nb_cmd)
	{
		j = 0;
		while (cmd[i].arg[j])
		{
			quote = quote_inside(cmd, i, j);
			printf("ARG[%d] quote = %d | = %s\n", j, quote, cmd[i].arg[j]);
			if (quote > 0)
				printf("il y a %d quote a l'enlever a l'interieur\n", quote);
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	char	**env_list;
	int		nb_cmd;

	cmd = NULL;
	(void)ac;
	(void)av;
	env_list = init_env(envp);
	signal(SIGINT, sig_handler);
	nb_cmd = 0;
	line = NULL;
	while (1)
	{
		line = readline("Minishell>");
		if (line)
			add_history(line);
		if (line == NULL)
			exit(1);
		nb_cmd = parse_command(line);
		if (nb_cmd >= 0)
		{
			printf("nb cmd %d\n", nb_cmd);
			cmd = malloc(sizeof(t_cmd) * (nb_cmd + 1));
			fill_cmd_array(line, cmd);
			format_args(cmd, env_list, nb_cmd);
			del_quotes(cmd, env_list, nb_cmd);
			parse_cmd_array(cmd, env_list, nb_cmd);
			free_after_line(cmd, line);
		}
		else if (line)
			free(line);
	}
	return (1);
}
