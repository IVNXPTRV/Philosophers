/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_philo_utils_libft.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhanenk <ikhanenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:34:58 by ikhanenk          #+#    #+#             */
/*   Updated: 2025/04/25 17:35:01 by ikhanenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		n;
	int		sign;
	char	*s;

	n = 0;
	sign = 1;
	s = (char *)str;
	while (*s && *s >= 9 && (*s <= 13 || *s == 32))
		s++;
	if (*s == '+')
		s++;
	if (*s && (*s == '-'))
	{
		sign = -sign;
		s++;
	}
	while (*s && *s >= '0' && *s <= '9')
		n = (n * 10) + (*s++ - '0');
	return (n * sign);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		counter += 1;
		i++;
	}
	return (counter);
}
