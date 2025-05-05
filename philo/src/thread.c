/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:25:24 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/25 03:57:33 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 *	RETURN VALUES
 *		If OKful, the pthread_create() function will return zero.  Otherwise an ER number will be returned to indicate the ER.
 *	ERS
 *		The pthread_create() function will fail if:
 *		[EAGAIN]           The system lacked the necessary resources to create another thread, / Error: Resource temporarily unavailable
 *		or the system-imposed limit on the total number of threads in a process [PTHREAD_THREADS_MAX] would be exceeded.
 *		[EPERM]            The caller does not have appropriate permission to set the required scheduling parameters or scheduling policy.
 *		[EINVAL]           The value specified by attr is invalid.
 */
t_sts th_create(pthread_t *tid, void *func(void *), void *arg)
{
	t_int	code;

	code = pthread_create(tid, NULL, func, arg);
	if (code == 0)
		return (OK);
	else if (code == EAGAIN)
		return (puterr("pthread_create: Error: Resource temporarily unavailable\n"));
	else if (code == EPERM)
		return (puterr("pthread_create: Error: Operation not permitted\n"));
	else if (code == EINVAL)
		return (puterr("pthread_create: Error: Invalid argument\n"));
	else
		return (ER);
}

/**
 *	RETURN VALUES
 *		If OKful, the pthread_join() function will return zero.  Otherwise, an ER number will be returned to indicate the ER.
 *	ERS
 *		The pthread_join() function will fail if:
 *		[EINVAL]           The implementation has detected that the value specified by thread does not refer to a joinable thread. / Error: Invalid argument
 *		[ESRCH]            No thread could be found corresponding to that specified by the given thread ID, thread. / Error: No such process
 *		[EDEADLK]          A deadlock was detected or the value of thread specifies the calling thread. / Error: Resource deadlock avoided
 */
t_sts th_join(pthread_t *tid)
{
	t_int	code;

	code = pthread_join(*tid, NULL);
	if (code == 0)
		return (OK);
	else if (code == EINVAL)
		return (puterr("pthread_join: Error: Invalid argument\n"));
	else if (code == ESRCH)
		return (puterr("pthread_join: Error: No such process\n"));
	else if (code == EDEADLK)
		return (puterr("pthread_join: Error: Resource deadlock avoided\n"));
	else
		return (ER);
}
