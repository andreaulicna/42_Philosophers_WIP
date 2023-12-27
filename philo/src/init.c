/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:36:07 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/27 21:23:03 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

int	init_mutexes(t_mutex *mutexes, int num_philos)
{
    int i;

	if (pthread_mutex_init(&mutexes->log, NULL))
        return (error(ERROR_MUTEX, NULL));
    mutexes->forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * num_philos);
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

int	init_party(t_party *party, t_input *input, t_mutex *mutexes)
{
	int	i;

	party->input = input;
	party->philos = (t_philo **) malloc(sizeof(t_philo *) * input->num_philos);
	if (!party->philos)
		return (error(ERROR_MALLOC, NULL));
	i = 0;
	party->mutexes = mutexes;
	while (i < input->num_philos)
	{
        party->philos[i] = (t_philo *) malloc (sizeof(t_philo));
        if (!party->philos[i])
		    return (error(ERROR_MALLOC, NULL));
		party->philos[i]->id = i;
		party->philos[i]->alive = 0;
		party->philos[i]->eat_rn = 0;
		party->philos[i]->meals_count = 0;
		party->philos[i]->last_meal = 0;
		party->philos[i]->right_fork = i;
		party->philos[i]->left_fork = i + 1;
		if (party->philos[i]->left_fork > input->num_philos)
			party->philos[i]->left_fork = 1;
		party->philos[i]->input = input;
		party->philos[i]->mutexes = mutexes;
		i++;
	}
	return (EXIT_SUCCESS);
}