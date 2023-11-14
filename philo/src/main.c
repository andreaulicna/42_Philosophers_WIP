/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:03:10 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/14 20:22:00 by aulicna          ###   ########.fr       */
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
	while (i < input->num_philos)
	{
		party->philos[i].id = i;
		party->philos[i].meals_count = 0;
		party->philos[i].last_meal = 0;
		party->philos[i].right_fork = i;
		party->philos[i].left_fork = i + 1;
		if (party->philos[i].left_fork > input->num_philos)
			party->philos[i].left_fork = 1;
		i++;
	}
	party->mutexes = mutexes;
	party->meet = get_time();
	
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

void	print_message(char *msg)
{
	printf("Hej: %s", msg);
}

void	*perform_routine(void *param)
{
	t_party	*party;

	party = param;
	pthread_mutex_lock(&party->mutexes->log);
	print_message("hou\n");
	pthread_mutex_unlock(&party->mutexes->log);
	return (NULL);
}

void handle_threads(t_party *party)
{
	int	i;

	i = 0;
	party->meet = get_time();
	while(i < party->input->num_philos)
	{
		party->philos[i].last_meal = get_time();
		pthread_create(&party->philos[i].thread, NULL, &perform_routine,
				&party->philos[i]);
		i++;
	}
	i = 0;
	while (i < party->input->num_philos)
	{
		pthread_join(party->philos[i].thread, NULL);
		i++;
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
		printf("Input error: Wrong number of arguments received.\n");
	return (0);
}