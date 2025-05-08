/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:09:48 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 06:44:54 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * RETURN VALUES
 *    If OKful, pthread_mutex_destroy() will return zero,
	otherwise an ER number will be returned to indicate the ER.
 *	ERS
 *  	The pthread_mutex_destroy() function will fail if:
 *   [EINVAL]           The value specified by mutex is invalid.
 *   [EBUSY]            Mutex is locked. / Error: Device or resource busy
 */
t_sts	mtx_destroy(t_mtx *mtx)
{
	t_sts	code;

	code = pthread_mutex_destroy(mtx);
	if (code == 0)
		return (OK);
	else if (code == EINVAL)
		return (puterr("pthread_mutex_destroy: Error: Invalid argument\n"));
	else if (code == EBUSY)
		return (puterr("pthread_mutex_destroy: Error: \
			Device or resource busy\n"));
	else
		return (ER);
}

/**
 *	RETURN VALUES
 *  	If OKful,
		pthread_mutex_init() will return zero and put the new
		mutex id into mutex,
		otherwise an ER number will be returned to indicate the ER.
 *	ERS
 *		The pthread_mutex_init() function will fail if:
 *		[EINVAL]           The value specified by attr is invalid.
			/ Error: Invalid argument

			*		[ENOMEM]           The process cannot allocate
			enough memory to create another mutex.
			/ Error: Cannot allocate memory
 */
t_sts	mtx_init(t_mtx *mtx)
{
	t_sts	code;

	code = pthread_mutex_init(mtx, NULL);
	if (code == 0)
		return (OK);
	else if (code == EINVAL)
		return (puterr("pthread_mutex_init: Error: Invalid argument\n"));
	else if (code == ENOMEM)
		return (puterr("pthread_mutex_init: Error: Cannot allocate memory\n"));
	else
		return (ER);
}

/**
 *	RETURN VALUES
 *		If OKful, pthread_mutex_lock() will return zero,
			otherwise an ER number will be returned to indicate the ER.
 *	ERS
 *		The pthread_mutex_lock() function will fail if:
 *		[EINVAL]           The value specified by mutex is invalid.
			/ Error: Invalid argument

			*		[EDEADLK]          A deadlock would occur if
			the thread blocked waiting for mutex.
			/ Error: Resource deadlock avoided
 */
t_sts	mtx_lock(t_mtx *lock)
{
	t_sts	code;

	code = pthread_mutex_lock(lock);
	if (code == 0)
		return (OK);
	else if (code == EINVAL)
		return (puterr("pthread_mutex_lock: Error: Invalid argument\n"));
	else if (code == EDEADLK)
		return (puterr("pthread_mutex_lock: Error: Resource \
			deadlock avoided\n"));
	else
		return (ER);
}

/**
 *	RETURN VALUES
 *		If OKful, pthread_mutex_unlock() will return zero,
			otherwise an ER number will be returned to indicate the ER.
 *	ERS
 *		The pthread_mutex_unlock() function will fail if:
 *		[EINVAL]           The value specified by mutex is invalid.
			/ Error: Invalid argument
 *		[EPERM]            The current thread does not hold a lock on mutex.
			/ Error: Operation not permitted
 */
t_sts	mtx_unlock(t_mtx *lock)
{
	t_sts	code;

	code = pthread_mutex_unlock(lock);
	if (code == 0)
		return (OK);
	else if (code == EINVAL)
		return (puterr("pthread_mutex_unlock: Error: Invalid argument\n"));
	else if (code == EDEADLK)
		return (puterr("pthread_mutex_lock: Error: Operation not permitted\n"));
	else
		return (ER);
}
