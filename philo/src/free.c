/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:05:29 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/27 19:04:59 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

void	free_party(t_party *party)
{
    int i;

    i = 0;
    while (i < party->input->num_philos)
    {
        free(party->philos[i]);
        i++;
    }
    free(party->mutexes->forks);
	free(party->philos);
}
