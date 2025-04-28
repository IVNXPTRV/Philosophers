/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_usleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:46:03 by dklimkin          #+#    #+#             */
/*   Updated: 2024/02/06 13:46:04 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_usleep(long long usec)
{
	long long	start;
	long long	end;

	start = get_timestamp();
	end = start + (usec / US_PER_MS);
	while (start < end)
	{
		if ((end - start) > 50000)
			usleep(40000);
		else if ((end - start) > 5000)
			usleep(4000);
		else
		{
			while (get_timestamp() < end)
				usleep(500);
			break ;
		}
		start = get_timestamp();
	}
}
