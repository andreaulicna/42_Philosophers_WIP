/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:05:29 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/30 11:07:48 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

void    destroy_mutexes(t_party *party)
{
    int i;

    pthread_mutex_destroy(&party->mutexes->log);
    i = 0;
    while (i < party->input->num_philos)
    {
        pthread_mutex_destroy(&party->philos[i]->philo_lock);
        pthread_mutex_destroy(&party->mutexes->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&party->party_on_lock);
}


void	free_party(t_party *party)
{
    int i;

    destroy_mutexes(party);
    if (party->mutexes->forks != NULL)
        free(party->mutexes->forks);
    i = 0;
    while (i < party->input->num_philos)
    {
        free(party->philos[i]);
        i++;
    }
	free(party->philos);
    printf("tu vo free\n");
}
