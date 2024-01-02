/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:36:07 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 14:56:24 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

/**
 * @brief	Initializes mutexes required for the philosopher simulation. These
 * are accessible via multiple structs.
 * 
 * Log:		logging output to the terminal
 * Forks:	a fork per philosopher
 *
 * @param	mutexes		t_mutex structure holding mutexes
 * @param	num_philos	number of philosophers in the simulation
 * @return	EXIT_SUCCESS on successful initialization, EXIT_FAILURE on error
 */
static int	init_mutexes(t_mutex *mutexes, int num_philos)
{
	int	i;

	if (pthread_mutex_init(&mutexes->log, NULL))
		return (error(ERROR_MUTEX, NULL));
	mutexes->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!mutexes->forks)
		return (error(ERROR_MALLOC, NULL));
	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_init(&mutexes->forks[i], NULL))
			return (error(ERROR_MUTEX, NULL));
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief	Assigns fork positions to a philosopher based on their index.
 * The fork a philo brings to the table is always the left one.
 * 
 * If there is only one philo in the simulation, the right_fork is left
 * unassigned as it will never be used.
 *
 * @param	philo	a philo to assign forks to
 * @param	input	input structure containing simulation parameters
 * @param	i		index of the philosopher
 */
static void	assign_forks(t_philo *philo, t_input *input, int i)
{
	philo->left_fork = i;
	if (input->num_philos != 1)
	{
		philo->right_fork = i + 1;
		if (philo->right_fork >= input->num_philos)
			philo->right_fork = 0;
	}
}

/**
 * @brief	Initializes the philosophers' data.
 * 
 * Each philo has a philo_lock mutex that safeguards the changes done
 * to the data in its struct.
 *
 * @param	party		overall simulation structure
 * @param	input		input structure containing simulation parameters
 * @param	mutexes		t_mutex structure holding already initialized mutexes
 * @return	EXIT_SUCCESS on successful initialization, EXIT_FAILURE on error
 */
static int	init_philos(t_party *party, t_input *input, t_mutex *mutexes)
{
	int	i;

	party->philos = (t_philo **) malloc(sizeof(t_philo *) * input->num_philos);
	if (!party->philos)
		return (error(ERROR_MALLOC, NULL));
	i = 0;
	while (i < input->num_philos)
	{
		party->philos[i] = (t_philo *) malloc (sizeof(t_philo));
		if (!party->philos[i])
			return (error(ERROR_MALLOC, NULL));
		party->philos[i]->input = input;
		party->philos[i]->mutexes = mutexes;
		party->philos[i]->id = i;
		party->philos[i]->meals_count = 0;
		party->philos[i]->last_meal = 0;
		party->philos[i]->eating_rn = 0;
		assign_forks(party->philos[i], input, i);
		if (pthread_mutex_init(&party->philos[i]->philo_lock, NULL))
			return (error(ERROR_MUTEX, NULL));
		party->philos[i]->party = party;
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief 	Initializes the main structure of the program, party, with necessary
 * data and mutexes.
 * 
 * There is a party_on mutex that safeguards changes to the simulation overall
 * status (whether or not it should continue running).
 *
 * @param	party		overall simulation structure
 * @param	input		input structure containing simulation parameters
 * @param	mutexes		t_mutex structure holding already initialized mutexes
 * @return	EXIT_SUCCESS on successful initialization, EXIT_FAILURE on error
 */
int	init_party(t_party *party, t_input *input, t_mutex *mutexes)
{
	party->input = input;
	if (init_mutexes(mutexes, input->num_philos))
		return (EXIT_FAILURE);
	party->mutexes = mutexes;
	if (init_philos(party, input, mutexes))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&party->party_on_lock, NULL))
		return (error(ERROR_MUTEX, NULL));
	party->party_on = 1;
	return (EXIT_SUCCESS);
}
