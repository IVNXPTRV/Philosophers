/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 04:44:38 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/16 06:04:31 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * @brief Retrieves the time elapsed in milliseconds since the simulation started.
 *
 * @param[out] timestamp The current timestamp in milliseconds since the simulation began.
 * @param start_time The timestamp in milliseconds marking the start of the simulation.
 * @return Status code.
 */
int	get_time(t_time *timestamp, t_time start_time)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == ERROR)
		return (puterr(ERRNAME"gettimeofday: error\n"));
	*timestamp = (tv.tv_sec * 1e3) + (tv.tv_usec / 1e3) - start_time;
	return (SUCCESS);
}
