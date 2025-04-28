/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sliashko <sliashko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:55:47 by sliashko          #+#    #+#             */
/*   Updated: 2024/02/07 17:59:33 by sliashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0

# define EAT "is eating"
# define THNK "is thinking"
# define SLEEP "is sleeping"

typedef struct philo_muts
{
	pthread_mutex_t	*print_mut;
	pthread_mutex_t	*exit_mut;
}		t_philo_muts;

typedef struct philo_data
{
	int				pos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				min_times_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	start_time;
	struct timeval	last_eat_time;
	int				*must_die;
	int				n;
	int				n_eats;
	t_philo_muts	*muts;
}		t_philo_data;

int				is_to_die(t_philo_data *philo);
void			create_mutexes(t_philo_data **philos);
t_philo_data	**init_philos(int argc, char **argv, int *DEATH_FLAG);
pthread_mutex_t	**init_forks(t_philo_data **philos);
void			set_start_time(t_philo_data **philos, int n);
long			get_curr_time(struct timeval start_time);
void			assign_forks(t_philo_data **philos, pthread_mutex_t **forks);
int				ft_atoi(const char *str);
int				message(char *msg, long time, int pos, t_philo_data *philo);
void			ft_usleep(long time_usec);
void			*philo(void	*data);
void			*death_checker(void	*philos_arr);
void			free_forks(pthread_mutex_t **forks, int n);
void			free_philos(t_philo_data **philos);
void			free_muts(t_philo_data *philo);

#endif
