/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:23:46 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/16 07:40:01 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * @brief Prints an error message to STDERR.
 *
 * This function writes a formatted error message to the standard error output.
 * Dont need to check for error we already almost exited
 *
 * @param msg The error message to print.
 * @return Always returns ERROR.
 */
int	puterr(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	return (ERROR);

}

/**
 * @brief
 *
 * @param msg
 * @return int
 */
int	putout(char *msg)
{
	if (write(STDOUT_FILENO, msg, ft_strlen(msg)) == ERROR)
		return (puterr(ERRNAME"write: failed\n"));
	return (SUCCESS);
}

static int get_first_msg_part(t_philo philo, char **result)
{
	int32_t	nbr;
	char	*time;
	char 	*id;

	if (get_time(&nbr, philo.ctx->start_time) != SUCCESS)
		return (ERROR);
	time = ft_itoa(nbr);
	if (!time)
		return (ERROR);
	id = ft_itoa(philo.id);
	if (!id)
	{
		free(time);
		time = NULL;
		return (ERROR);
	}
	*result = ft_strjoin(time, id);
	free(time);
	free(id);
	time = NULL;
	id = NULL;
	if (!*result)
		return (ERROR);
	return (SUCCESS);
}

/**
 * @brief
 * timestamp_in_ms X has taken a fork
 * timestamp_in_ms X is eating
 * timestamp_in_ms X is sleeping
 * timestamp_in_ms X is thinking
 * timestamp_in_ms X died
 * @param msg has to be with '/n' at the end
 */
int	put_philo_msg(t_philo philo, char *msg)
{
	char	*result;

	if (get_first_msg_part(philo, &result))
		return (ERROR);
	msg = ft_strjoin(result, msg);
	free(result);
	result = NULL;
	if (!msg)
		return (ERROR);
	if (putout(msg) != SUCCESS)
	{
		free(msg);
		msg = NULL;
		return (ERROR);
	}
	free(msg);
	msg = NULL;
	return (SUCCESS);
}


