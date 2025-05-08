/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 04:20:03 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 12:11:37 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * DESCRIPTION
		The system resources associated with the named semaphore referenced
		by sem are deallocated and the descriptor is invalidated.
		If successful, sem_close() will return 0.  Otherwise,
			-1 is returned and errno is set.

ERRORS
		sem_close() succeeds unless:
		[EINVAL]           sem is not a valid semaphore descriptor.
 */
t_sts	ft_sem_close(sem_t *sem)
{
	int	code;

	code = sem_close(sem);
	if (code == ER)
		return (puterr("sem_close: failed\n"));
	return (OK);
}

/**
 * DESCRIPTION
		The named semaphore named name is removed.  If the semaphore
		is in use by other processes,
		then name is immediately disassociated with the semaphore,
			but the semaphore itself will
		not be removed until all references to it have been closed.
		Subsequent calls to sem_open() using
		name will refer to or create a new semaphore named name.

		If successful, sem_unlink() will return 0.  Otherwise,
			-1 is returned and errno is set,
		and the state of the semaphore is unchanged.

ERRORS
		sem_unlink() succeeds unless:
		[EACCES]           Permission is denied to be remove
		the semaphore.
		[ENAMETOOLONG]     name exceeded PSEMNAMLEN characters.
		[ENOENT]           The named semaphore does not exist.
 */
t_sts	ft_sem_unlink(char *name)
{
	int	code;

	code = sem_unlink(name);
	if (code == EACCES || code == ENAMETOOLONG)
		return (puterr("sem_unlink: failed\n"));
	(void)code;
	return (OK);
}

/**
 * Automatically sem_unlink before open
 */
t_sts	ft_sem_open(sem_t **sem, char *name, t_int value)
{
	ft_sem_unlink(name);
	*sem = sem_open(name, O_CREAT, 0644, value);
	if (*sem == SEM_FAILED)
		return (puterr("sem_open: failed\n"));
	return (OK);
}

/**
 * DESCRIPTION
		The semaphore referenced by sem is unlocked,
			the value of the semaphore is incremented,
			and all threads which are waiting on the semaphore
			are awakened.
		sem_post() is reentrant with respect to signals and may be called
		from within a signal hanlder.
		If successful, sem_post() will return 0.  Otherwise,
			-1 is returned and errno is set.

ERRORS
		sem_post() succeeds unless:
		[EINVAL]           sem is not a valid semaphore descriptor.
 */
t_sts	ft_sem_post(sem_t *sem)
{
	int	code;

	code = sem_post(sem);
	if (code == ER)
		return (puterr("sem_post: failed\n"));
	return (OK);
}

/**
 * DESCRIPTION
		The semaphore referenced by sem is locked.  When calling sem_wait(),
			if the semaphore's value is zero,
			the calling thread will block until the lock is acquired or
			 until the call is interrupted by a signal. Alternatively,
			the sem_trywait() function will fail if the semaphore is
		already locked, rather than blocking on the semaphore.
		If successful (the lock was acquired),
			sem_wait() and sem_trywait() will return 0.  Otherwise,
			-1 is returned and errno is set,
			and the state of the semaphore is unchanged.
ERRORS
		sem_wait() and sem_trywait() succeed unless:
		[EAGAIN]           The semaphore is already locked.
		[EDEADLK]          A deadlock was detected.
		[EINTR]            The call was interrupted by a signal.
		[EINVAL]           sem is not a valid semaphore descriptor.
 */
t_sts	ft_sem_wait(sem_t *sem)
{
	int	code;

	code = sem_wait(sem);
	if (code == ER)
		return (puterr("sem_wait: failed\n"));
	return (OK);
}
