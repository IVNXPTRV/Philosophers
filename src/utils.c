/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:48:46 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/15 12:50:27 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * @brief Computes the length of the string.
 *
 * This function takes a constant character pointer as input and returns the
 * length of the string. If the input string is NULL, it returns 0.
 *
 * @param str The input string whose length is to be computed.
 * @return The length of the input string, or 0 if the input string is NULL.
 */
size_t	ft_strlen(const char *str)
{
	const char	*mem;

	if (!str)
		return (0);
	mem = str;
	while (*str)
		str++;
	return (str - mem);
}

/**
 * @brief Prints an error message to STDERR.
 *
 * This function writes a formatted error message to the standard error output.
 *
 * @param msg The error message to print.
 * @return Always returns ERROR.
 */
int	puterr(char *msg)
{
	write(STDERR_FILENO, "philo: ", 7);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (ERROR);
	// dont need to check for error we already almost exited
}


