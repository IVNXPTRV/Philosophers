/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 07:36:45 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/28 11:44:27 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// wait simulation begin
static inline t_sts stop_before_herd_gate(t_ctx *ctx)
{
	if (mtx_lock(&ctx->lock) != OK)
		return (FAIL);
	if (mtx_unlock(&ctx->lock) != OK)
		return (FAIL);
	return (OK);
}

static t_sts take_fork(t_fork *fork)
{
	while (true)
	{
		if (mtx_lock(&fork->lock) != OK)
			return (FAIL);
		if (fork->state == false)
		{
			fork->state = true;
			if (mtx_unlock(&fork->lock) != OK)
				return (FAIL);
			return (OK);
		}
		if (mtx_unlock(&fork->lock) != OK)
			return (FAIL);
	}
}

static t_sts take_forks(t_philo *philo, t_time now)
{
	if (take_fork(philo->fork_one) != OK)
		return (FAIL);
	if (putmsg(philo, now, FORK_1) != OK)
		return (FAIL);
	if (take_fork(philo->fork_two) != OK)
		return (FAIL);
	if (putmsg(philo, now, FORK_2) != OK)
		return (FAIL);
	return (OK);
}

static t_sts release_fork(t_fork *fork)
{
	while (true)
	{
		if (mtx_lock(&fork->lock) != OK)
			return (FAIL);
		if (fork->state == true)
		{
			fork->state = false;
			if (mtx_unlock(&fork->lock) != OK)
				return (FAIL);
			return (OK);
		}
		if (mtx_unlock(&fork->lock) != OK)
			return (FAIL);
	}
	return (OK);
}

static t_sts release_forks(t_philo *philo)
{
	if (release_fork(philo->fork_one) != OK)
		return (FAIL);
	if (release_fork(philo->fork_two) != OK)
		return (FAIL);
	return (OK);
}

// pass here ctx->lock and automatically unlock before return
inline t_sts is_end(t_ctx *ctx)
{
	if (ctx->end)
	{
		mtx_unlock(&ctx->lock);
		return (TRUE);
	}
	return (FALSE);
}

// sets ctx->end if died
// prints message is dead
t_sts is_dead(t_philo *philo, t_time now)
{
	if (now - philo->last_meal_time > philo->ctx->time_to_die)
	{
		philo->ctx->end = TRUE;
		putmsg(philo, now, DIED); // dont need to check for error we almost exited
		printf("\nOne philo is dead. Simulation is stopped.\n");
		mtx_unlock(&philo->ctx->lock);
		return (TRUE);
	}
	else
		return (FALSE);
}

// update last meal time
// increment cnsumed meals
inline t_sts	check_in_meal(t_philo *philo, t_time now)
{
	philo->last_meal_time = now;
	philo->meals_eaten += 1;
	return (OK);
}

// each file checks one time when he is full if we was last who need to be full
inline t_sts is_all_full(t_philo *philo)
{
	if (philo->ctx->meals_to_eat == UNDEFINED)
		return (FALSE);
	if (philo->meals_eaten == philo->ctx->meals_to_eat)
	{
		philo->ctx->num_full_philos += 1;
		if (philo->ctx->num_full_philos == philo->ctx->num_philos)
		{
			if (mtx_unlock(&philo->ctx->lock) != OK)
				return (FAIL);
			printf("\nAll philos are full. Simulation is stopped.\n");
			return (TRUE);
		}
	}
	return (FALSE);
}

// prevent deadlock and starvation
t_sts	philo_delay(t_philo *philo)
{
	// last philo if total num is odd will wait 2 eat times
	if (philo->id == philo->ctx->num_philos && philo->ctx->num_philos % 2)
	{
		if (smart_sleep(2 * philo->ctx->time_to_eat, philo->ctx) != OK)
			return (FAIL);
	}
	else
	{
		// each odd philo will wait 1 eat time
		if (philo->id % 2)
		{
			if (smart_sleep(philo->ctx->time_to_eat, philo->ctx) != OK)
				return (FAIL);
		}
		// each even philo will not wait
	}
	return (OK);
}

t_sts	philo_eat(t_philo *philo)
{
	t_time	now;

	if (mtx_lock(&philo->ctx->lock) != OK)
		return (FAIL);
	if (get_time(MS, &now, philo->ctx->start_time) != OK)
		return (FAIL); // unlock mtx here
	if (is_end(philo->ctx)) //
		return (FAIL);
	if (is_dead(philo, now))
		return (FAIL);
	if (take_forks(philo, now) != OK)
		return (FAIL); // unlock mtx here if failed
	check_in_meal(philo, now); // put last meal time using now and increment meals eaten
	if (putmsg(philo, now, EAT) != OK)
		return (FAIL); // unlock mtx here
	if (is_all_full(philo)) // check if full and if full increement global full philos and compare to total number and set end of sim if true
		return (FAIL);
	if (mtx_unlock(&philo->ctx->lock) != OK)
		return (FAIL);
	if (smart_sleep(philo->ctx->time_to_eat, philo->ctx) != OK)
		return (FAIL);
	if (release_forks(philo) != OK)
		return (FAIL);
	return (OK);
}

t_sts	philo_sleep(t_philo *philo)
{
	t_time	now;

	if (mtx_lock(&philo->ctx->lock) != OK)
		return (FAIL);
	if (get_time(MS, &now, philo->ctx->start_time) != OK)
		return (FAIL); // unlock mtx here
	if (is_end(philo->ctx)) //
		return (FAIL); // unlock mtx here
	if (is_dead(philo, now)) // set global sim end
		return (FAIL); // unlock mtx here
	if (putmsg(philo, now, SLEEP) != OK)
		return (FAIL); // unlock mtx here
	if (mtx_unlock(&philo->ctx->lock) != OK)
		return (FAIL);
	if (smart_sleep(philo->ctx->time_to_sleep, philo->ctx) != OK)
		return (FAIL);
	return (OK);
}

// maybe pass now time to eat fom here to think take forks and eat at same timestamp under one lock
// if time_to_think == 0
t_sts	philo_think(t_philo *philo)
{
	t_time	now;

	if (mtx_lock(&philo->ctx->lock) != OK)
		return (FAIL);
	if (get_time(MS, &now, philo->ctx->start_time) != OK)
		return (FAIL); // unlock mtx here
	if (is_end(philo->ctx)) //
		return (FAIL);
	if (is_dead(philo, now)) // set global sim end
		return (FAIL); // unlock mtx here
	if (putmsg(philo, now, THINK) != OK)
		return (FAIL); // unlock mtx here
	if (mtx_unlock(&philo->ctx->lock) != OK)
		return (FAIL);
	if (philo->ctx->time_to_think)
	{
		if (smart_sleep(philo->ctx->time_to_think, philo->ctx) != OK)
			return (FAIL);
	}
	return (OK);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	t_bool	end;

	philo = (t_philo *)ptr;
	end = false;
	if (stop_before_herd_gate(philo->ctx) != OK)
		end = true;
	if (!end && philo_delay(philo) != OK)
		end = true;
	while (!end)
	{
		if (philo_eat(philo) != OK)
			break ;
		if (philo_sleep(philo) != OK)
			break ;
		if (philo_think(philo) != OK)
			break ;
	}
	// set global simulation end to true
	mtx_lock(&philo->ctx->lock);
	philo->ctx->end = TRUE;
	mtx_unlock(&philo->ctx->lock);
	return (NULL);
}

// start simulation, open gate
t_sts open_herd_gate(t_ctx *ctx)
{
	if (mtx_unlock(&ctx->lock) != OK)
		return (ER);
	return (OK);
}

t_sts init_start_time(t_ctx *ctx)
{
	if (get_time(MS, &ctx->start_time, EPOCH) != OK)
		return (ER);
	return (OK);
}
/**
 * @brief
 * timestamp_in_ms X is thinking
 * timestamp_in_ms X has taken a fork
 * timestamp_in_ms X has taken a fork
 * timestamp_in_ms X is eating
 * timestamp_in_ms X is sleeping
 * timestamp_in_ms X died
 */
t_sts run_simulation(t_ctx *ctx)
{
	if (init_start_time(ctx) != OK)
		return (FAIL);
	if (open_herd_gate(ctx) != OK)
		return (FAIL);
	death_monitor(ctx);
	mtx_lock(&ctx->lock);
	ctx->end = TRUE;
	mtx_unlock(&ctx->lock);
	return (OK);
}
