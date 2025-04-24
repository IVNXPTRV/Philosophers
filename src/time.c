/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:44:38 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/24 02:21:06 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * @brief Retrieves the time elapsed in milliseconds since the simulation started.
 *
 *	RETURN
 *		A 0 return value indicates that the call succeeded.  A -1 return value indicates an error occurred, and in this case an error code is stored into the global variable errno.
 *	ERRORS
 *		The following error codes may be set in errno:
 *		[EFAULT]  An argument address referenced invalid memory. / Error: Bad address
 *		[EPERM]   A user other than the super-user attempted to set the time / Error: Operation not permitted
 * @param[out] timestamp The current timestamp in milliseconds since the simulation began.
 * @param start_time The timestamp in milliseconds marking the start of the simulation.
 * @return Status code.
 */
int	get_time(t_time *timestamp, t_time start_time)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == ERROR)
	{
		if (errno == EFAULT)
			return (puterr(ERRNAME"gettimeofday: Error: Bad address\n"));
		else if (errno == EPERM)
			return (puterr(ERRNAME"gettimeofday: Error: Operation not permitted\n"));
	}
	*timestamp = (tv.tv_sec * 1e3) + (tv.tv_usec / 1e3) - start_time;
	return (SUCCESS);
}

/**
 * @brief
 * RETURN VALUES
 *  The usleep() function returns the value 0 if successful; otherwise the value -1 is returned and the global variable errno is set to indicate the error.
 * ERRORS
 *  The usleep() function will fail if:
 *  [EINTR]            A signal was delivered to the process and its action was to invoke a signal-catching function. / Error: Interrupted system call
 * @param time
 * @return int
 */
int	philo_wait(t_time time)
{
	if (usleep(time * 1e3) == ERROR)
		return (puterr("usleep: Error: Interrupted system call\n"));
	return (SUCCESS);
}
