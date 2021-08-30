/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweglarz <lweglarz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:08:08 by user42            #+#    #+#             */
/*   Updated: 2021/08/30 13:38:05 by lweglarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "minishell.h"

size_t		ft_strlen(const char *str);
int			ft_strclen(const char *str, char c);
int			ft_isalnum(int c);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isascii(int c);
int			ft_str_isdigit(char *str);
int			ft_atoi(const char *nptr);

char		*ft_itoa(int n);
//static void	itoasign(int *n, unsigned int *sign);
//static int	lennb(int n);

char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split_slash(char const *s, char c);
char		**ft_split(const char *s, char c);

void	    free_splitnjoin(char **split);

#endif