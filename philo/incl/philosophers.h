/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:11:02 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 10:32:43 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_party	t_party;

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
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	unsigned long	meet;
}	t_input;

typedef struct s_mutex
{
	pthread_mutex_t	log;
	pthread_mutex_t	*forks;
}	t_mutex;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_count;
	unsigned long	last_meal;
	int				left_fork;
	int				right_fork;
	int				eating_rn;
	pthread_mutex_t	philo_lock;
	t_mutex			*mutexes;
	t_input			*input;
	t_party			*party;
}	t_philo;

typedef struct s_party
{
	t_input			*input;
	t_philo			**philos;
	t_mutex			*mutexes;
	pthread_t		thread;
	pthread_mutex_t	party_on_lock;
	int				party_on;
}	t_party;

// main.c
int				continue_run_party(t_party *party);

// input.c
void			read_input(t_input *input, int argc, char **argv);
void			check_input_for_numbers(int argc, char **argv);

// init.c
int				init_mutexes(t_mutex *mutexes, int num_philos);
int				init_party(t_party *party, t_input *input, t_mutex *mutexes);

// eat_sleep_think.c
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);

// party_run.c
void			*run_party(void *param);

// party_close.c
void			*close_party(void *param);

// change_mutex.c
void			change_party_on_via_mutex(t_party *party, int value);
void			change_meals_count_via_mutex(t_philo *philo);
void			change_last_meal_via_mutex(t_philo *philo);

// log.c
void			log_state_change(t_philo *philo, t_state state);
char			*get_state_change(t_state state);

// time.c
unsigned long	get_time(void);
void			delay(int delay_by);

// error.c
int				error(int error, t_party *party);

// free.c
void			free_party(t_party *party);

#endif