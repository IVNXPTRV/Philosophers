/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:25:24 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 06:48:41 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * DESCRIPTION
     fork() causes creation of a new process.  The new process (child process) is an exact copy of the calling process (parent process) except for the following:

           •   The child process has a unique process ID.
           •   The child process has a different parent process ID (i.e., the process ID of the parent process).
           •   The child process has its own copy of the parent's descriptors.  These descriptors reference the same underlying objects, so that, for instance, file pointers in file objects are shared between the child and the parent, so that an lseek(2) on a descriptor in the child
               process can affect a subsequent read or write by the parent.  This descriptor copying is also used by the shell to establish standard input and output for newly created processes as well as to set up pipes.
           •   The child processes resource utilizations are set to 0; see setrlimit(2).

RETURN VALUES
     Upon successful completion, fork() returns a value of 0 to the child process and returns the process ID of the child process to the parent process.  Otherwise, a value of -1 is returned to the parent process, no child process is created, and the global variable errno is set to
     indicate the error.

ERRORS
     fork() will fail and no child process will be created if:
     [EAGAIN]           The system-imposed limit on the total number of processes under execution would be exceeded.  This limit is configuration-dependent.
     [EAGAIN]           The system-imposed limit MAXUPRC (⟨sys/param.h⟩) on the total number of processes under execution by a single user would be exceeded.
     [ENOMEM]           There is insufficient swap space for the new process.
 */
t_sts ft_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid == ER)
		return (ER);
	return (OK);
}
