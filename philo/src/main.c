/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:03:10 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 14:30:38 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

/**
 * @brief	Starts the simulation by initializing philosopher threads and
 * setting the last_meal time for each philo to the meet time which is the time
 * the simulation started.
 *
 * If there are more than one philo, the function creates a thread from within
 * the party struct which monitors all the philo threads.
 *
 * @param	party		overall party structure
 * @return	EXIT_SUCCESS on successful simulation start, EXIT_FAILURE on error
 */
static int	start_party(t_party *party)
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
	if (party->input->num_philos != 1)
	{
		if (pthread_create(&party->thread, NULL, &close_party, party))
			return (error(ERROR_THREAD, party));
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief	Ends the philosopher party by joining threads by joining all 
 * the threads.
 * 
 * If there was a monitoring thread created (only if there is more than one
 * philo), it also joins that one.
 *
 * @param	party		overall party structure
 * @return	EXIT_SUCCESS on successful simulation start, EXIT_FAILURE on error
 */
static int	end_party(t_party *party)
{
	int	i;

	i = 0;
	while (i < party->input->num_philos)
	{
		pthread_join(party->philos[i]->thread, NULL);
		i++;
	}
	if (party->input->num_philos != 1)
		pthread_join(party->thread, NULL);
	return (EXIT_SUCCESS);
}

/**
 * @brief	Main function for executing the philosopher simulation.
 *
 * This function handles the main execution flow of the philosopher simulation
 * if an acceptable number of paramenters is provided. Otherwise an error
 * message detailing the correct usage of the program is printed.
 *
 * @param	argc	number of command-line arguments
 * @param	argv	array of command-line arguments
 * @return	EXIT_SUCCESS if successful, EXIT_FAILURE otherwise.
 */
int	main(int argc, char **argv)
{
	t_input	input;
	t_mutex	mutexes;
	t_party	party;

	if (argc == 5 || argc == 6)
	{
		check_input_for_numbers(argc, argv);
		read_input(&input, argc, argv);
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
