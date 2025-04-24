/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:23:46 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/24 13:05:21 by ipetrov          ###   ########.fr       */
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
int	puterr(char *msg)
{
	static t_mtx	lock = PTHREAD_MUTEX_INITIALIZER;

	mtx_lock(&lock);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	mtx_unlock(&lock);
	return (ER);
}

static char *get_msg(t_msg msg)
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
		return ("is died");
	return (NULL);
}

static int put_debug_msg(t_time now, t_philo *philo, t_msg msg)
{
	if (msg == FORK_1)
		return (printf(MSG" [%ld]\n", now, philo->id, get_msg(msg), philo->first_fork->id));
	if (msg == FORK_2)
		return (printf(MSG" [%ld]\n", now, philo->id, get_msg(msg), philo->second_fork->id));
	if (msg == EAT)
		return (printf(MSG" [%ld]\n", now, philo->id, get_msg(msg), philo->meals_eaten));
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
int	put_msg(t_philo *philo, t_msg msg)
{
	t_time			now;
	t_int			fork_num;
	static t_mtx	lock = PTHREAD_MUTEX_INITIALIZER;

	if (mtx_lock(&lock) != OK)
		return (ER);
	if (get_time(&now, philo->ctx->start_time) != OK)
		return (ER);
	now /= 1e3;
	if (now - philo->last_meal_time / 1e3 > philo->ctx->time_to_die / 1e3) // before print check if died
		return (OK);
	if (DEBUG)
		put_debug_msg(now, philo, msg);
	else if (printf(MSG"\n", now, philo->id, get_msg(msg)) < 0)
		return (puterr("printf: failed\n"));
	if (mtx_unlock(&lock) != OK)
		return (ER);
}

// //put_msg tester
// int main()
// {
// 	t_philo philo;
// 	t_ctx ctx;

// 	memset(&philo, 0, sizeof(t_philo));
// 	memset(&ctx, 0, sizeof(t_ctx));
// 	philo.ctx->time_to_die = 800 * 1e3;
// 	philo.ctx->start_time = get_time
// 	philo.ctx = &ctx;
// }