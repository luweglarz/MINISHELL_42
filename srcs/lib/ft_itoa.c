/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/05 16:31:47 by user42            #+#    #+#             */
/*   Updated: 2021/08/05 16:32:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	lennb(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		len++;
		if (len < 0)
			n = n * -1;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	itoasign(int *n, unsigned int *sign)
{
	if (*n < 0)
	{
		*n = *n * -1;
		*sign = 1;
	}
}

char	*ft_itoa(int n)
{
	unsigned int	len;
	unsigned int	sign;
	char			*str;

	len = lennb(n);
	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	itoasign(&n, &sign);
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	str[len--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (sign == 1)
		str[0] = '-';
	while (n != 0)
	{
		str[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (str);
}
