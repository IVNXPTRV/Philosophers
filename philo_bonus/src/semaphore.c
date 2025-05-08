/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 04:20:03 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 17:06:27 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * DESCRIPTION
     The system resources associated with the named semaphore referenced by sem are deallocated and the descriptor is invalidated.
     If successful, sem_close() will return 0.  Otherwise, -1 is returned and errno is set.

ERRORS
     sem_close() succeeds unless:
     [EINVAL]           sem is not a valid semaphore descriptor.
 */
t_sts ft_sem_close(sem_t *sem)
{
	int code;

	code = sem_close(sem);
	if (code == ER)
		return (puterr("sem_close: failed"));
	return (OK);
}

/**
 * DESCRIPTION
     The named semaphore named name is removed.  If the semaphore is in use by other processes,
	 then name is immediately disassociated with the semaphore, but the semaphore itself will
	 not be removed until all references to it have been closed.  Subsequent calls to sem_open() using
     name will refer to or create a new semaphore named name.

     If successful, sem_unlink() will return 0.  Otherwise, -1 is returned and errno is set,
	 and the state of the semaphore is unchanged.

ERRORS
     sem_unlink() succeeds unless:
     [EACCES]           Permission is denied to be remove the semaphore.
     [ENAMETOOLONG]     name exceeded PSEMNAMLEN characters.
     [ENOENT]           The named semaphore does not exist.
 */
t_sts ft_sem_unlink(char *name)
{
	int code;

	code = sem_unlink(name);
	if (code == EACCES || code == ENAMETOOLONG)
		return (puterr("sem_unlink: failed"));
	(void)code;
	return (OK);
}

/**
 * Automatically sem_unlink before open
 * DESCRIPTION
     The named semaphore named name is initialized and opened as specified by the argument oflag and a semaphore descriptor is returned to the calling process.
     The value of oflag is formed by or'ing the following values:
           O_CREAT         create the semaphore if it does not exist
           O_EXCL          error if create and semaphore exists
     If O_CREAT is specified, sem_open() requires an additional two arguments.  mode specifies the permissions for the semaphore as described in chmod(2) and modified by the process' umask value (see umask(2)).  The semaphore is created with an initial value, which must be less than
     or equal to SEM_VALUE_MAX.
     If O_EXCL is specified and the semaphore exists, sem_open() fails.  The check for the existence of the semaphore and the creation of the semaphore are atomic with respect to all processes calling sem_open() with O_CREAT and O_EXCL set.
     When a new semaphore is created, it is given the user ID and group ID which correspond to the effective user and group IDs of the calling process. There is no visible entry in the file system for the created object in this implementation.
     The returned semaphore descriptor is available to the calling process until it is closed with sem_close(), or until the caller exits or execs.
     If a process makes repeated calls to sem_open(), with the same name argument, the same descriptor is returned for each successful call, unless sem_unlink() has been called on the semaphore in the interim.
     If sem_open() fails for any reason, it will return a value of SEM_FAILED and sets errno.  On success, it returns a semaphore descriptor.

ERRORS
     The named semaphore is opened unless:
     [EACCES]           The required permissions (for reading and/or writing) are denied for the given flags; or O_CREAT is specified, the object does not exist, and permission to create the semaphore is denied.
     [EEXIST]           O_CREAT and O_EXCL were specified and the semaphore exists.
     [EINTR]            The sem_open() operation was interrupted by a signal.
     [EINVAL]           The shm_open() operation is not supported; or O_CREAT is specified and value exceeds SEM_VALUE_MAX.
     [EMFILE]           The process has already reached its limit for semaphores or file descriptors in use.
     [ENAMETOOLONG]     name exceeded PSEMNAMLEN characters.
     [ENFILE]           Too many semaphores or file descriptors are open on the system.
     [ENOENT]           O_CREAT is not set and the named semaphore does not exist.
     [ENOSPC]           O_CREAT is specified, the file does not exist, and there is insufficient space available to create the semaphore.
 */
t_sts ft_sem_open(sem_t **sem, char *name, t_int value)
{
	ft_sem_unlink(name);
	*sem = sem_open(name, O_CREAT, 0644, value);
	if (*sem == SEM_FAILED)
		return (puterr("sem_open: failed"));
	return (OK);
}

/**
 * DESCRIPTION
     The semaphore referenced by sem is unlocked, the value of the semaphore is incremented, and all threads which are waiting on the semaphore are awakened.
     sem_post() is reentrant with respect to signals and may be called from within a signal hanlder.
     If successful, sem_post() will return 0.  Otherwise, -1 is returned and errno is set.

ERRORS
     sem_post() succeeds unless:
     [EINVAL]           sem is not a valid semaphore descriptor.
 */
t_sts ft_sem_post(sem_t *sem)
{
	int code;

	code = sem_post(sem);
	if (code == ER)
		return (puterr("sem_post: failed"));
	return (OK);
}

/**
 * DESCRIPTION
     The semaphore referenced by sem is locked.  When calling sem_wait(), if the semaphore's value is zero, the calling thread will block until the lock is acquired or until the call is interrupted by a signal. Alternatively, the sem_trywait() function will fail if the semaphore is
     already locked, rather than blocking on the semaphore.
     If successful (the lock was acquired), sem_wait() and sem_trywait() will return 0.  Otherwise, -1 is returned and errno is set, and the state of the semaphore is unchanged.
ERRORS
     sem_wait() and sem_trywait() succeed unless:
     [EAGAIN]           The semaphore is already locked.
     [EDEADLK]          A deadlock was detected.
     [EINTR]            The call was interrupted by a signal.
     [EINVAL]           sem is not a valid semaphore descriptor.
 */
t_sts ft_sem_wait(sem_t *sem)
{
	int code;

	code = sem_wait(sem);
	if (code == ER)
		return (puterr("sem_wait: failed"));
	return (OK);
}

