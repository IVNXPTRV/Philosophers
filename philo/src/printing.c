/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:23:46 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/30 10:19:02 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * @brief Prints an ER message to STDERR.
 *
 * This function writes a formatted ER message to the standard ER output.
 * Dont need to check for ER we already almost exited
 *
 * @param msg The ER message to print.
 * @return Always returns ER.
 */
t_sts	puterr(char *msg)
{
	static t_mtx	lock = PTHREAD_MUTEX_INITIALIZER;
	ssize_t			i;

	mtx_lock(&lock);
	i = write(STDERR_FILENO, msg, ft_strlen(msg));
	(void)i;
	mtx_unlock(&lock);
	return (ER);
}

static char	*get_msg(t_msg msg)
{
	if (msg == FORK_1 || msg == FORK_2)
		return ("has taken a fork");
	if (msg == EAT)
		return ("is eating");
	if (msg == SLEEP)
		return ("is sleeping");
	if (msg == THINK)
		return ("is thinking");
	if (msg == DIED)
		return ("died");
	return (NULL);
}

static t_sts	put_debug_msg(t_time now, t_philo *philo, t_msg msg)
{
	if (msg == FORK_1)
		return (printf(MSG " [%lld]\n", now, philo->id, get_msg(msg),
				philo->fork_one->id));
	if (msg == FORK_2)
		return (printf(MSG " [%lld]\n", now, philo->id, get_msg(msg),
				philo->fork_two->id));
	if (msg == EAT)
		return (printf(MSG " [%lld]\n", now, philo->id, get_msg(msg),
				philo->meals_eaten));
	if (msg == SLEEP || msg == THINK || msg == DIED)
		return (printf(MSG "\n", now, philo->id, get_msg(msg)));
	return (OK);
}

/**
 * @brief
 * Automatically gets current time for timestamp
 * timestamp_in_ms X has taken a fork
 * timestamp_in_ms X is eating
 * timestamp_in_ms X is sleeping
 * timestamp_in_ms X is thinking
 * timestamp_in_ms X died
 * @param msg has to be with '/n' at the end
 */
t_sts	putmsg(t_philo *philo, t_time now, t_msg msg)
{
	if (DEBUG)
		put_debug_msg(now, philo, msg);
	else if (printf(MSG "\n", now, philo->id, get_msg(msg)) < 0)
		return (puterr("printf: failed\n"));
	return (OK);
}
