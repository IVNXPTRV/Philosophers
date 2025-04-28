/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 07:36:45 by ipetrov           #+#    #+#             */
/*   Updated: 2025/04/28 07:14:48 by ipetrov          ###   ########.fr       */
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

static t_sts take_forks(t_philo *philo)
{
	if (take_fork(&philo->fork_one) != OK)
		return (FAIL);
	if (putmsg(philo, FORK_1) != OK)
		return (FAIL);
	if (take_fork(&philo->fork_two) != OK)
		return (FAIL);
	if (putmsg(philo, FORK_2) != OK)
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
	if (release_fork(&philo->fork_one) != OK)
		return (FAIL);
	if (release_fork(&philo->fork_two) != OK)
		return (FAIL);
	return (OK);
}

// pass here ctx->lock and automatically unlock before return
inline t_sts is_end(t_ctx *ctx)
{
	return (ctx->end);
}

// sets ctx->end if died
// prints message is dead
t_sts is_dead(t_philo *philo, t_time now)
{
	if (now - philo->last_meal_time > philo->ctx->time_to_die)
	{
		philo->ctx->end = TRUE;
		putmsg(philo, DIED); // dont need to check for error we almost exited
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
			return (TRUE);
	}
	else
		return (FALSE);
}

// prevent deadlock and starvation
t_sts	philo_delay(t_philo *philo)
{
	// last philo if total num is odd will wait 2 eat times
	if (philo->id == philo->ctx->num_philos && philo->ctx->num_philos % 2)
	{
		if (psleep(2 * philo->ctx->time_to_eat) != OK)
			return (ER);
	}
	else
	{
		// each odd philo will wait 1 eat time
		if (philo->id % 2)
		{
			if (psleep(philo->ctx->time_to_eat) != OK)
				return (ER);
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
	if (get_time(&now, philo->ctx->start_time) != OK)
		return (FAIL); // unlock mtx here
	if (is_end(philo->ctx)) //
		return (FAIL); // unlock mtx here
	if (is_dead(philo, now)) // set global sim end
		return (FAIL); // unlock mtx here
	if (take_forks(philo) != OK)
		return (FAIL); // unlock mtx here
	if (putmsg(philo, EAT) != OK)
		return (FAIL); // unlock mtx here
	check_in_meal(philo, now); // put last meal time using now and increment meals eaten
	if (is_all_full(philo)) // check if full and if full increement global full philos and compare to total number and set end of sim if true
		return (FAIL);
	if (mtx_unlock(&philo->ctx->lock) != OK)
		return (FAIL);
	if (psleep(&philo->ctx->time_to_eat) != OK)
		return (FAIL);
	if (release_forks(philo) != OK)
		return (FAIL);
	return (OK);
}

t_sts	philo_sleep(t_philo *philo)
{
	t_time	now;

	if (mtx_lock(&philo->ctx->lock) != OK)
		return (ER);
	if (is_end())//??
		return (ER); // unlock mtx here
	if (get_time(&now, philo->ctx->start_time) != OK)
		return (ER); // unlock mtx here
	if (is_dead())//?? //set global sim end
		return (ER); // unlock mtx here
	if (putmsg(philo, SLEEP) != OK)
		return (ER); // unlock mtx here
	if (psleep(&philo->ctx->time_to_sleep) != OK)
		return (ER);
	return (OK);
}

t_sts	philo_think(t_philo *philo)
{
	t_time	now;

	if (mtx_lock(&philo->ctx->lock) != OK)
		return (ER);
	if (is_end())//??
		return (ER); // unlock mtx here
	if (get_time(&now, philo->ctx->start_time) != OK)
		return (ER); // unlock mtx here
	if (is_dead())//?? //set global sim end
		return (ER); // unlock mtx here
	if (putmsg(philo, THINK) != OK)
		return (ER); // unlock mtx here
	if (philo->ctx->time_to_think)
	{
		if (psleep(&philo->ctx->time_to_think) != OK)
			return (ER);
	}
	return (OK);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	t_sts	status;

	philo = (t_philo *)ptr;
	status = RUNNING;
	if (stop_before_herd_gate(philo) != OK)
		status = END;
	if (status != END && philo_delay(philo) != OK)
		status = END;
	while (status != END)
	{
		if (philo_eat(philo) != OK)
			break ;
		if (philo_sleep(philo) != OK)
			break ;
		if (philo_think(philo) != OK)
			break ;
	}
	// set global simulation end status = END
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
	if (get_time(US, &ctx->start_time, EPOCH) != OK)
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
	t_int	status;
	t_int	i;

	if (init_start_time(ctx) != OK)
		return (ER);
	if (open_herd_gate(ctx) != OK)
		return (ER);
	while (true)
	{
		i = -1;
		while (++i < ctx->num_philos)
		{
			if (is_dead(ctx->philos[i] != OK))
				return (ER);
		}
		if (is_end(ctx) != OK) //
			return (ER);
		//sleep less 20 ms
		usleep(15000);
	}
	return (OK);
}

// if (get_val(&ctx->lock, &ctx->status, &status) != OK) // get status of simulation
// return (ER);
// if (status == DIED) // check if anyone died -- check status if 2, someone died
// return (OK);
// else if (status == ER) // check if any ER reported to finish execution
// return (ER);
// if (ctx->philos_full == -1) // check if we had number of meals in arguments
// continue ;
// if (get_val(&ctx->lock, &ctx->philos_full, &status) != OK) // get number of full philos
// return (ER);
// if (status == ctx->num_philos) // check if all full
// return (OK);