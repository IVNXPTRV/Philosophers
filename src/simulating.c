/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 07:36:45 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/16 13:01:12 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int wait_simulation_begin(t_ctx *ctx)
{
	int32_t	status;

	status = true;
	while (status)
	{
		if (get_val(&ctx->lock, &ctx->status, &status, sizeof(int32_t)) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

static int philo_takes_forks(t_philo *philo)
{
	t_time	time;

	if (mtx_lock(&philo->first_fork->lock) != SUCCESS)//take fork1
		return (ERROR);
	if (get_time(&time, philo->ctx->start_time) != SUCCESS)
		return (ERROR);
	if (put_philo_msg(philo, time, "has taken a fork\n") != SUCCESS)
		return (ERROR);
	if (mtx_lock(&philo->second_fork->lock) != SUCCESS)//take fork2
		return (ERROR);
	if (get_time(&time, philo->ctx->start_time) != SUCCESS)
		return (ERROR);
	if (put_philo_msg(philo, time, "has taken a fork\n") != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

static int philo_eats_or_dies(t_philo *philo)
{
	t_time	time;

	if (get_time(&time, philo->ctx->start_time) != SUCCESS)
		return (ERROR);
	if (time <= philo->ctx->time_to_die) // TODO: check if less ot less or equal
	{
		if (put_philo_msg(philo, time, "is eating\n") != SUCCESS)
			return (ERROR);
		if (philo_wait(philo->ctx->time_to_eat) != SUCCESS)
			return (ERROR);
	}
	else
	{
		if (put_philo_msg(philo, time, "died\n") != SUCCESS)
			return (ERROR);
		if (set_val(&philo->ctx->lock, &philo->ctx->status, &(int32_t){DIED}, sizeof(int32_t)) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

static int philo_sleeps(t_philo *philo)
{
	t_time	time;

	if (get_time(&time, philo->ctx->start_time) != SUCCESS)
		return (ERROR);
	if (put_philo_msg(philo, time, "is sleeping\n") != SUCCESS)
		return (ERROR);
	if (philo_wait(philo->ctx->time_to_sleep) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

static int philo_thinks(t_philo *philo)
{
	t_time	time;

	if (get_time(&time, philo->ctx->start_time) != SUCCESS)
		return (ERROR);
	// wait a little bit to prevent startvation??
	if (put_philo_msg(philo, time, "is thinking\n") != SUCCESS)
		return (ERROR);
	if (philo_wait(1) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

static int is_end(t_philo *philo, int32_t *status)
{
	int32_t	ctx_sts;

	if (get_val(&philo->ctx->lock, &philo->ctx->status, &ctx_sts, sizeof(int32_t)) != SUCCESS)
		return (ERROR);
	if (ctx_sts != RUN)
		*status = ctx_sts;
	return (SUCCESS);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	int32_t	status;

	philo = (t_philo *)ptr;
	if (wait_simulation_begin(philo->ctx) != SUCCESS)
	{
		set_val(&philo->ctx->lock, &philo->ctx->status, &(int32_t){ERROR}, sizeof(int32_t));
		return ((void *)ERROR);
	}
	status = RUN;
	while (status == RUN)
	{
		if (philo_takes_forks(philo) != SUCCESS) // take both forks
			return (ERRPTR);
		else if (philo_eats_or_dies(philo) != SUCCESS) // eats and check if too late
			return (ERRPTR);
		else if (is_end(philo, &status) != SUCCESS) // check if anyone dead or any errors
			return (ERRPTR);
		else if (philo_sleeps(philo) != SUCCESS) // sleep
			return (ERRPTR);
		else if (philo_thinks(philo) != SUCCESS) // think
			return (ERRPTR);
	}
	return (SUCPTR);
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
	int32_t	status;

	if (get_time(&ctx->start_time, 0) != SUCCESS)
		return (ERROR);
	if (set_val(&ctx->lock, &ctx->status, &(int32_t){RUN}, sizeof(int32_t)) != SUCCESS)
		return (ERROR);
	while (true)
	{
		if (get_val(&ctx->lock, &ctx->status, &status, sizeof(int32_t)) != SUCCESS)
			return (ERROR);
		if (status == DIED) // check if anyone died -- check status if 2, someone died
			return (SUCCESS);
		else if (status == ERROR) // check if any error reported to finish execution
			return (ERROR);
		if (ctx->philos_full == -1)
			continue ;
		if (get_val(&ctx->lock, &ctx->philos_full, &status, sizeof(int32_t)) != SUCCESS)
			return (ERROR);
		if (status == ctx->nbr_philos) // check if all full
			return (SUCCESS);
	}
	return (SUCCESS);
}
