/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:03:10 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/25 17:59:32 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	in_ms;

	gettimeofday(&time, NULL);
	in_ms = (time.tv_sec * 1000) + (time.tv_sec / 100);
	return (in_ms);
}

int	init_party(t_party *party, t_input *input, t_mutex *mutexes)
{
	int	i;

	party->input = input;
	party->philos = (t_philo *) malloc(sizeof(t_philo) * input->num_philos);
	if (!party->philos)
		return (error('A'));
	i = 0;
	party->mutexes = mutexes;
	while (i < input->num_philos)
	{
		party->philos[i].id = i;
		party->philos[i].alive = 0;
		party->philos[i].eat_rn = 0;
		party->philos[i].meals_count = 0;
		party->philos[i].last_meal = 0;
		party->philos[i].right_fork = i;
		party->philos[i].left_fork = i + 1;
		if (party->philos[i].left_fork > input->num_philos)
			party->philos[i].left_fork = 1;
		party->philos[i].input = input;
		party->philos[i].mutexes = mutexes;
		i++;
	}
	
	return (0);
}

void	only_one(t_input *input)
{
	usleep(input->time_to_die * 1000);
	printf("%-5d %-1d %s\n", input->time_to_die, input->num_philos, DIED);
	exit(0);
}

void	free_party(t_party *party)
{
	free(party->philos);
}

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutexes->log);
	printf("%-5ld %-1d %s\n", get_time() - philo->input->meet, philo->id,
		"is thinking");
	pthread_mutex_unlock(&philo->mutexes->log);
	philo->alive = 1;
}

void	eat(t_philo *philo)
{
	philo->eat_rn = 0;
	printf("%-5ld %-1d %s\n", get_time() - philo->input->meet, philo->id,
		"is eating");
	
}

void	*perform_routine(void *param)
{
	t_philo	*philo;
	int	i;

	philo = param;
	i = 0;
	if (philo->id % 2 == 0)
		eat(philo);
	while (philo->alive != 1)
	{
		think(philo);
		i++;
	}
	return (NULL);
}

void handle_threads(t_party *party)
{
	int	i;
	int	j;

	i = 0;
	while(i < party->input->num_philos)
	{
		party->philos[i].last_meal = get_time();
		pthread_create(&party->philos[i].thread, NULL, &perform_routine,
				&party->philos[i]);
		i++;
	}
	j = 0;
	while (j < party->input->num_philos)
	{
		pthread_join(party->philos[j].thread, NULL);
		j++;
	}
	pthread_mutex_destroy(&party->mutexes->log);
}

void	init_mutexes(t_mutex *mutexes)
{
	pthread_mutex_init(&mutexes->log, NULL);
}

int	main(int argc, char **argv)
{
	t_input	input;
	t_mutex	mutexes;
	t_party	party;

	if (argc == 5 || argc == 6)
	{
		check_input_for_numbers(argc, argv);
		read_input(&input, argc, argv);
		if (input.num_philos == 1)
			only_one(&input);
		init_mutexes(&mutexes);
		init_party(&party, &input, &mutexes);
		handle_threads(&party);
		free_party(&party);
	}
	else
	{
		printf("Input error: Wrong number of arguments received.\n");
		printf("Correct usage: ./philo number_of_philosophers time_to_die "
				"time_to_eat time_to_sleep " 
				"[number_of_times_each_philosopher_must_eat]\n\n");
	}
	return (0);
}