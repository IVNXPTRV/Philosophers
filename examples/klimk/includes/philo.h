/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:59:19 by dklimkin          #+#    #+#             */
/*   Updated: 2024/01/23 16:59:20 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>

// magic numbers
# define UNSPECIFIED -2
# define ERROR -1
# define SUCCESS 0
# define FAILURE 1

# define MAX_MS_TO_ANNOUNCE_DEATH 10

# define MS_PER_SEC 1000
# define US_PER_MS 1000

// error messages
# define NOT_ENOUGH_ARGS_ERR "Not enough arguments provided\n"
# define INVALID_ARGS_ERR "Provided arguments are not valid\n"
# define UNKNOWN_ERR "Unknown error occurred\n"

// log messages
# define THINK "is thinking"
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define DIE "died"

// structures
typedef struct s_sim_params
{
	int		number_of_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_meals;
}	t_sim_params;

typedef enum e_stop_event
{
	NO_STOP_EVENT,
	PHILO_DIED,
	NO_MEALS_LEFT,
}	t_stop_event;

typedef struct s_sim_status
{
	pthread_mutex_t	mutex;
	bool			should_stop;
	t_stop_event	stop_event;
	int				philo_id;
}	t_sim_status;

typedef struct s_sim_log
{
	pthread_mutex_t	mutex;
	long long		start_time;
}	t_sim_log;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_meal
{
	pthread_mutex_t	mutex;
	int				number_of_meals_left;
	long long		last_meal;
}	t_meal;

typedef struct s_philo
{
	int				id;
	t_sim_params	sim_params;
	t_sim_status	*sim_status;
	t_sim_log		*sim_log;
	long			sim_start_delay;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_meal			*meal;
}	t_philo;

typedef struct s_sim
{
	t_sim_params	params;
	t_sim_status	status;
	t_sim_log		log;
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		*threads;
}	t_sim;

// functions
// /src
long long		get_timestamp(void);
void			smart_usleep(long long usec);

t_sim_params	parse_params(int argc, char **argv);
int				init_sim(t_sim **sim, t_sim_params params);
void			run_sim(t_sim **sim);

int				create_threads(t_sim **sim);
void			join_threads(t_sim **sim);

void			*philo_routine(void *arg);
bool			is_philo_dead(t_philo *philo);
bool			has_philo_meals_left(t_philo *philo);

int				try_take_forks(t_philo *philo);
void			release_forks(t_philo *philo);

int				print_log(t_philo *philo, char *message);
int				print_log_with_status_check(t_philo *philo, char *message);

int				handle_cleanup(t_sim **sim);
int				exit_with_error_message(char *err_msg);

// /utils
int				ft_atoi(const char *str);
char			**ft_split(char const *s, char c);
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlen(const char *s);

#endif
