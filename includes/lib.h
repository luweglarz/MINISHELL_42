/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:08:08 by user42            #+#    #+#             */
/*   Updated: 2021/07/02 01:08:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "minishell.h"

size_t		ft_strlen(const char *str);
int			ft_strclen(const char *str, char c);

int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isascii(int c);
int	        ft_atoi(const char *nptr);

char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strschr(char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2);

char		**free_words(int word, char **tabword);
const char	*pass_quotes(const char *str, int *inquote);
int			count_words(const char *str, char c);
int			ft_word_len(const char *s, char c);
const char	*fill_quoted_word(const char *s, char *tab, int *inquote);
char		**ft_split_args(char const *s, char c);

int	check_inquote2(int c, int inquote);

#endif