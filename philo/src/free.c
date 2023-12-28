/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:05:29 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/28 21:38:37 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

void    destroy_mutexes(t_party *party)
{
    int i;

    pthread_mutex_destroy(&party->mutexes->log);
    pthread_mutex_destroy(&party->mutexes->party_on);
    i = 0;
    while (i < party->input->num_philos)
    {
        pthread_mutex_destroy(&party->mutexes->forks[i]);
        i++;
    }
}


void	free_party(t_party *party)
{
    int i;

    destroy_mutexes(party);
    i = 0;
    while (i < party->input->num_philos)
    {
        free(party->philos[i]);
        i++;
    }
    free(party->mutexes->forks);
	free(party->philos);
}
