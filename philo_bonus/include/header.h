/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:49:44 by ipetrov           #+#    #+#             */
/*   Updated: 2025/05/08 11:56:51 by ipetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <errno.h>
# include <fcntl.h> /* For O_* constants */
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define DEBUG false
# define UNDEFINED -1
# define TRUE true
# define FALSE false
# define OK 1
# define ER -1
# define FAIL 0
# define EPOCH 0
# define WAIT 1
# define RUN 0
# define PRNME "philo: "
# define ANYPID -1
# define LOCKNME "/lock"
# define FORKSNME "/forks"
# define FULLNME "/full"
# define ERPTR "\xFF"
# define OKPTR "\x01"
# define MSG "%lld %lld %s"
# define TIMEOUT 1000
# define RED "\033[31m"
# define RESET "\033[0m\n"

typedef long long int	t_int;
typedef double			t_dec;
typedef t_int			t_sts;
typedef t_int			t_bool;
typedef t_int			t_time;

typedef struct s_ctx	t_ctx;
typedef pthread_mutex_t	t_mtx;
typedef pthread_t		t_tid;

enum					e_atoi_codes
{
	NEGATIVE = 2,
	NONNUM,
	OVERFLOW32,
};

typedef enum e_msg
{
	FORK_1,
	FORK_2,
	EAT,
	SLEEP,
	THINK,
	DIED,
	FULL,
}						t_msg;

typedef enum e_time_type
{
	US,
	MS
}						t_time_type;

typedef struct s_philo
{
	t_int				id;
	pid_t				pid;

	t_ctx				*ctx;
	t_int				meals_eaten;
	t_time				last_meal_time;
}						t_philo;

/*
 * context
 */
typedef struct s_ctx
{
	sem_t				*lock;
	sem_t				*full;

	t_int				num_philos;
	t_bool				end;
	t_int				num_full_philos;
	t_int				meals_to_eat;
	t_time				time_to_die;
	t_time				time_to_eat;
	t_time				time_to_sleep;
	t_time				time_to_think;
	t_time				start_time;

	t_philo				philos[200];
	sem_t				*forks;
}						t_ctx;

/*
 * UTILS
 */
size_t					ft_strlen(const char *str);
t_sts					ft_atoi(t_int *num, char *str);
void					*ft_calloc(size_t num, size_t size);
char					*ft_strjoin(char const *s1, char const *s2);
void					*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * PRINT
 */
t_sts					puterr(char *msg);
t_sts					putmsg(t_philo *philo, t_time now, t_msg msg);

/**
 * STATUS
 */
t_sts					is_dead(t_philo *philo, t_time now, t_int flag);
t_sts					is_end(t_ctx *ctx);

/**
 * TIME
 */
t_sts					get_time(t_time_type type, t_time *dst,
							t_time start_time);
t_sts					smart_sleep(t_time waittime, t_philo *philo);
t_sts					sched(void);

/**
 * PARSING
 */
t_sts					parse_input(t_ctx *ctx, t_int ac, char **av);

/**
 * SIMULATING
 *
 */
t_sts					run_simulation(t_ctx *ctx);
void					*philo_routine(void *ptr);
t_sts					check_in_meal(t_philo *philo, t_time now);
t_sts					is_all_full(t_philo *philo);
t_sts					take_forks(t_philo *philo);
t_sts					release_forks(t_philo *philo);
t_sts					philo_eat(t_philo *philo);

/**
 * INITIALIZING
 *
 */
t_sts					init_data(t_ctx *ctx);
t_sts					init_start_time(t_ctx *ctx);

/**
 * MONITOR
 *
 */
t_sts					end_monitor(t_ctx *ctx);

/**
 * SEMAPHORE
 *
 */
t_sts					ft_sem_open(sem_t **sem, char *name, t_int value);
t_sts					ft_sem_close(sem_t *sem);
t_sts					ft_sem_unlink(char *name);
t_sts					ft_sem_post(sem_t *sem);
t_sts					ft_sem_wait(sem_t *sem);

/**
 * MUTEX
 *
 */
t_sts					mtx_lock(t_mtx *lock);
t_sts					mtx_unlock(t_mtx *lock);

/**
 * THREAD
 *
 */
t_sts					th_create(pthread_t *tid, void *func(void *),
							void *arg);
t_sts					th_join(pthread_t *tid);

/**
 * FORK
 *
 */
t_sts					ft_fork(pid_t *pid);

/**
 * CLEANING
 *
 */
t_int					clean_sem(char *name, sem_t *sem);
t_int					clean_philos(t_ctx *ctx);
t_sts					clean_ctx(t_ctx *ctx);
t_sts					clean(t_ctx *ctx);

#endif