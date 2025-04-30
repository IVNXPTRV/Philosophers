/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:44:38 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/30 09:33:25 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// start_time -- time elapsed from start time, 0 if full epoch
/**
 * @brief Retrieves the time elapsed in microseconds since the starting point
 *
 *	RETURN
 *		A 0 return value indicates that the call succeeded.  A -1 return value indicates an ER occurred, and in this case an ER code is stored into the global variable errno.
 *	ERS
 *		The following ER codes may be set in errno:
 *		[EFAULT]  An argument address referenced invalid memory. / Error: Bad address
 *		[EPERM]   A user other than the super-user attempted to set the time / Error: Operation not permitted
 * @param[out] dst The current timestamp in microseconds since the simulation began.
 * @param start_time The timestamp in microseconds marking the start of the simulation.
 * @return Status code.
 */
t_sts	get_time(t_time_type type, t_time *dst, t_time start_time)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == ER)
	{
		if (errno == EFAULT)
			return (puterr(PRNME"gettimeofday: Error: Bad address\n"));
		else if (errno == EPERM)
			return (puterr(PRNME"gettimeofday: Error: Operation not permitted\n"));
	}
	if (type == MS)
	{
		*dst = (tv.tv_sec * 1e3) + (tv.tv_usec / 1e3) - start_time;
	}
	else // US
	{
		*dst = (tv.tv_sec * 1e6) + tv.tv_usec - start_time;
	}
	return (OK);
}

/**
 * @brief Precise sleep, more accurate then usleep
 * RETURN VALUES
 *  The usleep() function returns the value 0 if OKful; otherwise the value -1 is returned and the global variable errno is set to indicate the ER.
 * ERS
 *  The usleep() function will fail if:
 *  [EINTR]            A signal was delivered to the process and its action was to invoke a signal-catching function. / Error: Interrupted system call
 * @param waittime // in ms
 * @return int
 */
t_sts	smart_sleep(t_time waittime, t_ctx *ctx)
{
	t_time	start;
	t_time	timeout;
	t_time	now;
	t_time	rem;

	if (get_time(US, &start, EPOCH) != OK)
		return (ER);
	waittime *= 1e3;
	rem = waittime;
	timeout = TIMEOUT * 1e3;
	while (rem > 1e3)
	{
		if (rem > timeout) // 100 000 timeout to check if simulation ended
		{
			if (usleep(timeout - 2e3) == ER)
				return (puterr("usleep: Error: Interrupted system call\n"));
			if (mtx_lock(&ctx->lock) != OK)
				return (FAIL);
			if (is_end(ctx)) //
				return (FAIL); // unlock mtx here
			if (mtx_unlock(&ctx->lock) != OK)
				return (FAIL);
		}
		else
		{
			if (usleep(rem / 2) == ER)
				return (puterr("usleep: Error: Interrupted system call\n"));
		}
		if (get_time(US, &now, EPOCH) != OK)
			return (ER);
		rem = waittime - (now - start);
	}
	while (now - start < waittime)
	{
		if (get_time(US, &now, EPOCH) != OK)
			return (ER);
	}
	return (OK);
}
