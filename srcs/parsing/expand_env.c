/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugtheven <ugtheven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 12:57:08 by ugtheven          #+#    #+#             */
/*   Updated: 2021/07/01 13:00:21 by ugtheven         ###   ########.fr       */
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
	while (line[*index] && line[*index] != ' ' && line[*index] != '\'' && line[*index] != '"'
		&& line[*index] != ';' && line[*index] != '|' && line[*index] != '$')
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
	char	*str;
	char	*temp;
	int		start;
	int		end;

	start = 0;
	end = (int)ft_strlen(tmp);
	while (tmp[start] && tmp[start] == ' ')
		start++;
	while (end > 0 && tmp[end] == ' ')
		end--;
	str = ft_substr(tmp, start, end);
	temp = ft_strjoin("\"", str);
	free(str);
	str = ft_strjoin(temp, "\"");
	free(temp);
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
		tmp = ft_getenv(var_name, env_list);
	if (var_name)
		free(var_name);
	if (tmp && space == 0)
		var_content = strdup_without_space(tmp);
	else if (tmp && space == 1)
	{
		var_content = malloc(sizeof(char) * ft_strlen(tmp) + 3);
		var_content[0] = '"';
		while (tmp[i++])
			var_content[i] = tmp[i - 1];
		var_content[ft_strlen(tmp) + 1] = '"';
		var_content[ft_strlen(tmp) + 2] = '\0';
		
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
		inquote = check_inquote(line, stop, inquote);
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

char	*replace_env_var(const char *line, char **env_list, int i, int stop)
{
	int		inquote;
	t_pars	pars;

	inquote = 0;
	init_env_parse(&pars);
	while (line[i])
	{
		inquote = check_inquote(line, i, inquote);
		if (line[i] == '$' && (inquote == 0 || inquote == 2))
		{
			if (pars.res == NULL && inquote == 2)
				pars.res = ft_substr(line, 0, i - 1);
			else if (pars.res == NULL)
				pars.res = ft_substr(line, 0, i);
			else if (line[stop + i - stop])
				pars.tmp2 = ft_substr(line, stop, i - stop);
			i++;
			if (inquote == 2)
				pars.expanded = expand_var_content(line, &i, env_list, 0, 1);
			else if (i < (int)ft_strlen(line) && line[i] != ';' && line[i + 1] && line[i + 1] != ' ')
			{
				inquote = check_inquote(line, i, inquote);
				if (inquote == 0)
					pars.expanded = expand_var_content(line, &i, env_list, 0, 0);
				else if (inquote == 1)
					pars.expanded = del_dollar(&line[i], '\'');
				else
					pars.expanded = del_dollar(&line[i], '"');
			}
			else
				pars.expanded = ft_strdup("$");
			stop = i;
		}
		if (pars.expanded || pars.tmp2)
		{
			if (pars.tmp2)
			{
				pars.tmp = ft_strdup(pars.res);
				free(pars.res);
				pars.res = NULL;
				pars.res = ft_strjoin(pars.tmp, pars.tmp2);
				free(pars.tmp);
				pars.tmp = NULL;
				free(pars.tmp2);
				pars.tmp2 = NULL;
			}
			if (pars.expanded)
			{
				pars.tmp = ft_strdup(pars.res);
				free(pars.res);
				pars.res = ft_strjoin(pars.tmp, pars.expanded);
				free(pars.tmp);
				pars.tmp = NULL;
				free(pars.expanded);
				pars.expanded = NULL;
			}
		}
		if (i < (int)ft_strlen(line) && line[i] != '$')
			i++;
	}
	if (pars.res == NULL)
		pars.res = ft_substr(line, 0, i);
	else if (stop != i)
	{
		pars.tmp = ft_strdup(pars.res);
		pars.tmp2 = ft_substr(line, stop, i - stop);
		free(pars.res);
		pars.res = ft_strjoin(pars.tmp, pars.tmp2);
		free(pars.tmp);
		free(pars.tmp2);
	}
	return (pars.res);
}
