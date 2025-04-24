/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 07:36:45 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/24 13:05:21 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int wait_simulation_begin(t_ctx *ctx)
{
	t_int	status;

	status = true;
	while (status)
	{
		if (get_val(&ctx->lock, &ctx->status, &status) != OK)
			return (ER);
	}
	return (OK);
}

static int philo_takes_forks(t_philo *philo)
{
	t_time	time;

	if (mtx_lock(&philo->first_fork->lock) != OK) // take fork1
		return (ER);
	if (get_time(&time, philo->ctx->start_time) != OK)
		return (ER);
	if (DEBUG)
		mtx_printf("has taken a fork [%ld]\n", time, philo->id, philo->first_fork->id);
	else if (put_philo_msg(philo, time, "has taken a fork\n") != OK)
		return (ER);
	if (mtx_lock(&philo->second_fork->lock) != OK) // take fork2
		return (ER);
	if (get_time(&time, philo->ctx->start_time) != OK)
		return (ER);
	if (DEBUG)
		mtx_printf("has taken a fork [%ld]\n", time, philo->id, philo->second_fork->id);
	else if (put_philo_msg(philo, time, "has taken a fork\n") != OK)
		return (ER);
	return (OK);
}

static int philo_puts_forks(t_philo *philo)
{
	if (mtx_unlock(&philo->first_fork->lock) != OK)
		return (ER);
	if (mtx_unlock(&philo->second_fork->lock) != OK)
		return (ER);
	return (OK);
}

static int philo_eats_or_dies(t_philo *philo)
{
	// t_time	timestamp;
	t_time	time;			//

	if (get_time(&time, philo->last_meal_time) != OK)
		return (ER);
	if (time <= philo->ctx->time_to_die) // TODO: check if less ot less or equal
	{
		philo->last_meal_time = time;
		if (put_philo_msg(philo, time, "is eating\n") != OK)
			return (ER);
		if (philo_wait(philo->ctx->time_to_eat) != OK)
			return (ER);
	}
	else
	{
		if (put_philo_msg(philo, time, "died\n") != OK)
			return (ER);
		if (set_val(&philo->ctx->lock, &philo->ctx->status, &(t_int){DIED}) != OK)
			return (ER);
	}
	if (philo_puts_forks(philo) != OK)
		return (ER);
	return (OK);
}

static int philo_sleeps(t_philo *philo)
{
	t_time	time;

	if (get_time(&time, philo->ctx->start_time) != OK)
		return (ER);
	if (put_philo_msg(philo, time, "is sleeping\n") != OK)
		return (ER);
	if (philo_wait(philo->ctx->time_to_sleep) != OK)
		return (ER);
	return (OK);
}

static int philo_thinks(t_philo *philo)
{
	t_time	time;

	if (get_time(&time, philo->ctx->start_time) != OK)
		return (ER);
	if (put_philo_msg(philo, time, "is thinking\n") != OK)
		return (ER);
	if (philo_wait(1) != OK) 	// wait a little bit to prevent startvation??
		return (ER);
	return (OK);
}

static int is_end(t_philo *philo, t_int *status)
{
	t_int	ctx_sts;

	if (get_val(&philo->ctx->lock, &philo->ctx->status, &ctx_sts) != OK)
		return (ER);
	if (ctx_sts != RUN)
		*status = ctx_sts;
	return (OK);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	t_int	status;

	philo = (t_philo *)ptr;
	if (wait_simulation_begin(philo->ctx) != OK)
	{
		set_val(&philo->ctx->lock, &philo->ctx->status, &(t_int){ER});
		return ((void *)ER);
	}
	status = RUN;
	while (status == RUN)
	{
		if (philo_takes_forks(philo) != OK) // take both forks
			return (ERPTR);
		else if (philo_eats_or_dies(philo) != OK) // eats and checks if too late
			return (ERPTR);
		else if (is_end(philo, &status) != OK) // check if anyone dead or any ERs
			return (ERPTR);
		else if (philo_sleeps(philo) != OK) // sleep
			return (ERPTR);
		else if (philo_thinks(philo) != OK) // think
			return (ERPTR);
	}
	return (OKPTR);
}

/**
 * @brief
 * timestamp_in_ms X has taken a fork
 * timestamp_in_ms X is eating
 * timestamp_in_ms X is sleeping
 * timestamp_in_ms X is thinking
 * timestamp_in_ms X died
 * @param msg has to be with '/n' at the end
 */
int run_simulation(t_ctx *ctx)
{
	t_int	status;

	if (get_time(&ctx->start_time, 0) != OK)
		return (ER);
	if (set_val(&ctx->lock, &ctx->status, &(t_int){RUN}) != OK)
		return (ER);
	while (true)
	{
		if (get_val(&ctx->lock, &ctx->status, &status) != OK) // get status of simulation
			return (ER);
		if (status == DIED) // check if anyone died -- check status if 2, someone died
			return (OK);
		else if (status == ER) // check if any ER reported to finish execution
			return (ER);
		if (ctx->philos_full == -1) // check if we had number of meals in arguments
			continue ;
		if (get_val(&ctx->lock, &ctx->philos_full, &status) != OK) // get number of full philos
			return (ER);
		if (status == ctx->num_philos) // check if all full
			return (OK);
	}
	return (OK);
}
// DIED, FULL, ER