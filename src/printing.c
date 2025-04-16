/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:23:46 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/16 11:55:29 by ipetrov          ###   ########.fr       */
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
	static t_mtx	lock = PTHREAD_MUTEX_INITIALIZER;

	mtx_lock(&lock);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	mtx_unlock(&lock);
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
	static t_mtx	lock = PTHREAD_MUTEX_INITIALIZER;

	if (mtx_lock(&lock) != SUCCESS)
		return (ERROR);
	if (write(STDOUT_FILENO, msg, ft_strlen(msg)) == ERROR)
		return (puterr(ERRNAME"write: failed\n"));
	if (mtx_unlock(&lock) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

static int get_first_msg_part(t_philo *philo, t_time time, char **result)
{
	char	*timestr;
	char 	*id;

	timestr = ft_itoa(time);
	if (!timestr)
		return (ERROR);
	id = ft_itoa(philo->id);
	if (!id)
	{
		free(timestr);
		timestr = NULL;
		return (ERROR);
	}
	*result = ft_strjoin(timestr, id);
	free(timestr);
	free(id);
	timestr = NULL;
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
int	put_philo_msg(t_philo *philo, t_time time, char *msg)
{
	char	*result;
	int32_t	status;

	if (get_first_msg_part(philo, time, &result))
		return (ERROR);
	msg = ft_strjoin(result, msg);
	free(result);
	result = NULL;
	if (!msg)
		return (ERROR);
	if (get_val(&philo->ctx->lock, &philo->ctx->status, &status, sizeof(int32_t)) != SUCCESS)
	{
		free(msg);
		msg = NULL;
		return (ERROR);
	}
	if (status != RUN && putout(msg) != SUCCESS)
	{
		free(msg);
		msg = NULL;
		return (ERROR);
	}
	free(msg);
	msg = NULL;
	return (SUCCESS);
}


