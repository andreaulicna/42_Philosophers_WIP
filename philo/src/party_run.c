/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:16:20 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 10:17:28 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	continue_run_party(t_party *party)
{
	int	signal;

	signal = 1;
	pthread_mutex_lock(&party->party_on_lock);
	if (party->party_on == 0)
		signal = 0;
	pthread_mutex_unlock(&party->party_on_lock);
	return (signal);
}

void	*run_party(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	if (philo->input->must_eat == 0)
		return (NULL);
	if (philo->id % 2 != 1)
	{
		philo_think(philo);
		delay(philo->input->time_to_eat);
	}
	while (continue_run_party(philo->party))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
