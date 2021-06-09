/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 12:13:53 by lweglarz          #+#    #+#             */
/*   Updated: 2021/06/09 16:18:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_cmd
{
		char			*builtin;
		char			*arg;
		char			*option;
}				t_cmd;

typedef	struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;


int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		parse_line(const char *line);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **alst, t_list *new);

#endif