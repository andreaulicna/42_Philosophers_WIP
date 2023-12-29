/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:11:02 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/29 13:14:46 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_S
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum s_erors
{
	ERROR_MALLOC = 2,
	ERROR_MUTEX,
	ERROR_THREAD,
}	t_errors;

typedef enum s_state
{
	LEFT_FORK = 1,
	RIGHT_FORK,
	EAT,
	SLEEP,
	THINK,
	DIED
}	t_state;

typedef struct s_input
{
	int		num_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		must_eat;
	time_t	meet;
	int		party_on;
} t_input;

typedef struct s_mutex
{
	pthread_mutex_t	log;
	pthread_mutex_t *forks;
	pthread_mutex_t party_on;
}	t_mutex;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_count;
	time_t			last_meal;
	int				left_fork;
	int				right_fork;
	pthread_mutex_t	philo_lock;
	t_mutex			*mutexes;
	t_input			*input;
} t_philo;

typedef struct s_party
{
	t_input		*input;
	t_philo		**philos;
	t_mutex		*mutexes;
	pthread_t	thread;

} t_party;

// main.c
int		continue_run_party(t_philo *philo);

// input.c
void	read_input(t_input *input, int argc, char **argv);
void	check_input_for_numbers(int argc, char **argv);

// init.c
int		init_mutexes(t_mutex *mutexes, int num_philos);
int		init_party(t_party *party, t_input *input, t_mutex *mutexes);

// eat_sleep_think.c
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo, int log);

// log.c
void    log_state_change(t_philo *philo, t_state state);
char    *get_state_change(t_state state);

// time.c
int		get_time(void);
int		get_time_to_print(int meet);
void	delay(t_philo *philo, time_t delay_by);

// error.c
int	error(int error, t_party *party);

// free.c
void	free_party(t_party *party);

#endif