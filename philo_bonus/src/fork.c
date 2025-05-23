/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:25:24 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 12:12:20 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_sts	ft_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid == ER)
		return (ER);
	return (OK);
}
