/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:47:40 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/15 11:48:10 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

inline static	bool is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

inline  static	bool is_numeric(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(int64_t *nbr, char *str)
{
	char	digit;

	*nbr = 0;
	while (is_whitespace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (puterr(ERRNAME"each argument has to be positive\n"));
	while (is_numeric(*str))
	{
		digit = *str - '0';
		if (*nbr > (INT32_MAX - digit) / 10)
			return (puterr(ERRNAME"each argument has to be not greater than INT_MAX\n"));
		*nbr = *nbr * 10 + *str - '0';
		str++;
	}
	if (*str != '\0')
		return (puterr(ERRNAME"each argument has to be numeric only\n"));
	return (SUCCESS);
}

static int	get_num_length(int64_t n)
{
	int64_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

//modified version adds space at the end
char	*ft_itoa(int64_t n)
{
	char		*str;
	int64_t		len;

	len = get_num_length(n);
	str = (char *)ft_calloc(len + 2, sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	str[len] = ' ';
	while (n > 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
