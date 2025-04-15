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

int	ft_atoi(int *nbr, char *str)
{
	char	digit;

	*nbr = 0;
	while (is_whitespace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (puterr("arguments have to be positive"));
	while (is_numeric(*str))
	{
		digit = *str - '0';
		if (*nbr > (INT32_MAX - digit) / 10)
			return (puterr("arguments have to be less than INT_MAX"));
		*nbr = *nbr * 10 + *str - '0';
		str++;
	}
	if (*str != '\0')
		return (puterr("argumens have to be numeric only"));
	return (SUCCESS);
}

// int main()
// {
// 	int nbr;
// 	int code;

// 	code = ft_atoi(&nbr, "ad2147483647");
// 	printf("code: %d\nnbr: %d\n", code, nbr);
// }