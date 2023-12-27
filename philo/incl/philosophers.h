/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:11:02 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/27 15:19:18 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_S
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define DIED "died"
# define ERROR_MALLOC 2

typedef struct s_input
{
	int	num_philos;
	int	time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int	must_eat;
	int		meet;
} t_input;

typedef struct s_mutex
{
	pthread_mutex_t	log;
}	t_mutex;

typedef struct s_philo
{
	pthread_t		thread;
	int	id;
	int	alive;
	int	eat_rn;
	int	meals_count;
	unsigned long	last_meal;
	int	left_fork;
	int	right_fork;
	t_mutex	*mutexes;
	t_input	*input;
} t_philo;

typedef struct s_party
{
	t_input	*input;
	t_philo	**philos;
	t_mutex	*mutexes;
} t_party;

// input.c
void	read_input(t_input *input, int argc, char **argv);
void	check_input_for_numbers(int argc, char **argv);

// init.c
void	init_mutexes(t_mutex *mutexes);
int	init_party(t_party *party, t_input *input, t_mutex *mutexes);

// time.c
int	get_time_to_print(int meet);
int	get_time(void);

// error.c
int	error(int error);

#endif