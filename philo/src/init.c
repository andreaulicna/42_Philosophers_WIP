/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:36:07 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/01 21:20:19 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

int	init_mutexes(t_mutex *mutexes, int num_philos)
{
    int i;

	if (pthread_mutex_init(&mutexes->log, NULL))
        return (error(ERROR_MUTEX, NULL));
    mutexes->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
    if (!mutexes->forks)
        return(error(ERROR_MALLOC, NULL));
    i = 0;
    while (i < num_philos)
    {
        if (pthread_mutex_init(&mutexes->forks[i], NULL))
            return (error(ERROR_MUTEX, NULL));
        i++;
    }
    return (EXIT_SUCCESS);
}

int	init_philos(t_party *party, t_input *input, t_mutex *mutexes)
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
		party->philos[i]->left_fork = i;
		party->philos[i]->right_fork = i + 1;
		if (party->philos[i]->right_fork >= input->num_philos)
			party->philos[i]->right_fork = 0;
		if (pthread_mutex_init(&party->philos[i]->philo_lock, NULL))
        	return (error(ERROR_MUTEX, NULL));
		party->philos[i]->party = party;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_party(t_party *party, t_input *input, t_mutex *mutexes)
{
	party->input = input;
	party->mutexes = mutexes;
	if (init_philos(party, input, mutexes))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&party->party_on_lock, NULL))
        return (error(ERROR_MUTEX, NULL));
	party->party_on = 1;
	return (EXIT_SUCCESS);
}

