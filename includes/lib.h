/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 22:08:08 by user42            #+#    #+#             */
/*   Updated: 2021/06/17 18:10:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isascii(int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strcmp(char *s1, char *s2);

#endif