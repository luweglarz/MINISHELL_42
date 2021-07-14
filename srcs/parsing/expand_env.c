/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:57:08 by ugtheven          #+#    #+#             */
/*   Updated: 2021/07/14 02:44:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(const char *line, int *index)
{
	char	*var_name;
	int		i;
	int		j;

	j = 0;
	i = *index;
	while (line[*index] && line[*index] != ' ' && line[*index] != '\''
		&& line[*index] != '"' && line[*index] != ';'
		&& line[*index] != '|' && line[*index] != '$')
	{
		*index = *index + 1;
		j++;
	}
	var_name = malloc(sizeof(char) * j + 1);
	j = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\'' && line[i] != '"'
		&& line[i] != ';' && line[i] != '|' && line[i] != '$')
	{
		var_name[j] = line[i];
		i++;
		j++;
	}
	var_name[j] = '\0';
	return (var_name);
}

char	*strdup_without_space(char *tmp)
{
	char	**tab;
	char	*str;
	int		i;
	int		j;
	int		count;

	tab = ft_split(tmp, ' ');
	count = 0;
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			j++;
			count++;
		}
		i++;
		count++;
	}
	str = malloc(sizeof(char) * count + 2);
	count = 1;
	i = 0;
	str[0] = '"';
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			str[count] = tab[i][j];
			j++;
			count++;
		}
		str[count] = ' ';
		i++;
		count++;
	}
	str[count - 1] = '"';
	str[count] = '\0';
	return (str);
}

char	*expand_var_content(const char *line, int *index, char **env_list, int i, int space)
{
	char	*var_name;
	char	*var_content;
	char	*tmp;

	var_name = get_var_name(line, index);
	var_content = NULL;
	tmp = NULL;
	if (getenv(var_name) != NULL)
	{
		tmp = ft_getenv(var_name, env_list);
		printf("content brute : '%s'\n", tmp);
	}
	if (var_name)
		free(var_name);
	if (tmp && space == 0)
	{
		var_content = strdup_without_space(tmp);
		printf("content w- space uniquement : '%s'\n", var_content);
	}
	else if (tmp && space == 1)
	{
		var_content = malloc(sizeof(char) * ft_strlen(tmp) + 3);
		var_content[0] = '"';
		while (tmp[i++])
			var_content[i] = tmp[i - 1];
		var_content[ft_strlen(tmp) + 1] = '"';
		var_content[ft_strlen(tmp) + 2] = '\0';
		printf("content w+ space uniquement : '%s'\n", var_content);
	}
	if (tmp)
		free(tmp);
	return(var_content);
}

char	*del_dollar(const char *line, char quote)
{
	char	*expanded;
	int		stop;
	int		inquote;
	int		i;

	stop = 1;
	inquote = 0;
	while (line[stop])
	{
		inquote = check_inquote(line[stop], inquote);
		if (inquote == 0)
			break;
		stop++;
	}
	expanded = malloc(sizeof(char) * stop + 1);
	i = 0;
	while (line[i++])
		expanded[i - 1] = line[i];
	expanded[0] = quote;
	expanded[stop - 1] = quote;
	expanded[stop] = '\0';
	return (expanded);
}

void	save_buffer(t_pars *pars, const char *line, int *i)
{
	if (pars->res == NULL && pars->inquote == 2)
		pars->res = ft_substr(line, 0, *i - 1);
	else if (pars->res == NULL)
		pars->res = ft_substr(line, 0, *i);
	else if (line[pars->stop + *i - pars->stop])
		pars->tmp2 = ft_substr(line, pars->stop, *i - pars->stop);
	*i = *i + 1;
}

void	add_buffer(t_pars *pars)
{
	pars->tmp = ft_strdup(pars->res);
	free(pars->res);
	pars->res = NULL;
	pars->res = ft_strjoin(pars->tmp, pars->tmp2);
	free(pars->tmp);
	pars->tmp = NULL;
	free(pars->tmp2);
	pars->tmp2 = NULL;
}

void	add_expansion(t_pars *pars)
{
	pars->tmp = ft_strdup(pars->res);
	printf("pars->res = '%s'\n", pars->res);
	printf("pars->expanded = '%s'\n", pars->expanded);
	free(pars->res);
	pars->res = ft_strjoin(pars->tmp, pars->expanded);
	printf("AFTER JOIN pars->res = '%s'\n", pars->res);
	free(pars->tmp);
	pars->tmp = NULL;
	free(pars->expanded);
	pars->expanded = NULL;
}

void	add_last_buffer(t_pars *pars, const char *line, int i)
{
	pars->tmp = ft_strdup(pars->res);
	pars->tmp2 = ft_substr(line, pars->stop, i - pars->stop);
	free(pars->res);
	pars->res = ft_strjoin(pars->tmp, pars->tmp2);
	free(pars->tmp);
	free(pars->tmp2);
}

void	get_expanded(t_pars *pars, char **env_list, const char *line, int *i)
{
	pars->inquote = check_inquote(line[*i], pars->inquote);
	if (pars->inquote == 0)
		pars->expanded = expand_var_content(line, i, env_list, 0, 0);
	else if (pars->inquote == 1)
	{
		pars->expanded = del_dollar(&line[*i], '\'');
		printf("[DEBUG2]del_dollar\n");
	}
	else
	{
		pars->expanded = del_dollar(&line[*i], '"');
		printf("[DEBUG2]del_dollar\n");
	}
}

void	choose_expansion(t_pars *pars, const char *line, int *i, char **env_list)
{
	save_buffer(pars, line, i);
	if (pars->inquote == 2)
	{
		pars->expanded = expand_var_content(line, i, env_list, 0, 1);
		printf("Le $ est entre double quote\n");
	}
	else if (*i < (int)ft_strlen(line) && line[*i] != ';' && line[*i + 1] && line[*i + 1] != ' ')
	{
		get_expanded(pars, env_list, line, i);
		printf("[DEBUG2]\n");
	}
	else
		pars->expanded = ft_strdup("$");
	pars->stop = *i;
}

char	*replace_env_var(const char *line, char **env_list, int i)
{
	t_pars	pars;

	init_env_parse(&pars);
	while (line[i])
	{
		pars.inquote = check_inquote(line[i], pars.inquote);
		if (line[i] == '$' && (pars.inquote == 0 || pars.inquote == 2))
			choose_expansion(&pars, line, &i, env_list);
		if (pars.expanded || pars.tmp2)
		{
			if (pars.tmp2)
				add_buffer(&pars);
			if (pars.expanded)
				add_expansion(&pars);
		}
		if (i < (int)ft_strlen(line) && line[i] != '$')
			i++;
	}
	if (pars.res == NULL)
		pars.res = ft_substr(line, 0, i);
	else if (line[i] != '\0')
		add_last_buffer(&pars, line, i);
	return (pars.res);
}
