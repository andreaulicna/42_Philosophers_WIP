/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:36:07 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/27 15:23:44 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

void	init_mutexes(t_mutex *mutexes)
{
	pthread_mutex_init(&mutexes->log, NULL);
}

int	init_party(t_party *party, t_input *input, t_mutex *mutexes)
{
	int	i;

	party->input = input;
	party->philos = (t_philo **) malloc(sizeof(t_philo *) * input->num_philos);
	if (!party->philos)
		return (error(ERROR_MALLOC));
	i = 0;
	party->mutexes = mutexes;
	while (i < input->num_philos)
	{
        party->philos[i] = (t_philo *) malloc (sizeof(t_philo));
        if (!party->philos[i])
		    return (error(ERROR_MALLOC));
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
	return (0);
}