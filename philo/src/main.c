/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:03:10 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/13 21:19:26 by aulicna          ###   ########.fr       */
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

int	init_party(t_party *party, t_input *input)
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

void	*perform_routine(void *party)
{
	(void) party;
	printf("%-5ld %-1d %s\n", get_time(), 2, "runs.");
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
}

int	main(int argc, char **argv)
{
	t_input	input;
	t_party	party;

	if (argc == 5 || argc == 6)
	{
		check_input_for_numbers(argc, argv);
		read_input(&input, argc, argv);
		if (input.num_philos == 1)
			only_one(&input);
		init_party(&party, &input);
		handle_threads(&party);
		free_party(&party);
	}
	else
		printf("Input error: Wrong number of arguments received.\n");
	return (0);
}