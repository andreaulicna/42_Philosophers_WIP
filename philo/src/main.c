/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:03:10 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 10:20:21 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	only_one_philo(t_input *input)
{
	input->meet = get_time();
	printf("%lu %d %s\n", get_time() - input->meet, 1,
		get_state_change(LEFT_FORK));
	delay(input->time_to_die);
	printf("%lu %d %s\n", get_time() - input->meet, 1,
		get_state_change(DIED));
	exit(0);
}

int	start_party(t_party *party)
{
	int	i;

	party->input->meet = get_time();
	i = 0;
	while (i < party->input->num_philos)
	{
		if (pthread_create(&party->philos[i]->thread, NULL, &run_party,
				party->philos[i]))
			return (error(ERROR_THREAD, party));
		pthread_mutex_lock(&party->philos[i]->philo_lock);
		party->philos[i]->last_meal = party->input->meet;
		pthread_mutex_unlock(&party->philos[i]->philo_lock);
		i++;
	}
	if (pthread_create(&party->thread, NULL, &close_party, party))
		return (error(ERROR_THREAD, party));
	return (EXIT_SUCCESS);
}

int	end_party(t_party *party)
{
	int	i;

	i = 0;
	while (i < party->input->num_philos)
	{
		pthread_join(party->philos[i]->thread, NULL);
		i++;
	}
	pthread_join(party->thread, NULL);
	return (EXIT_SUCCESS);
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
			only_one_philo(&input);
		if (init_party(&party, &input, &mutexes))
			return (EXIT_FAILURE);
		if (start_party(&party))
			return (EXIT_FAILURE);
		end_party(&party);
		free_party(&party);
	}
	else
	{
		printf("Input error: Wrong number of arguments received.\n\n");
		printf("Correct usage: ./philo number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n\n");
	}
	return (EXIT_SUCCESS);
}
