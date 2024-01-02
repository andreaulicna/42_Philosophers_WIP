/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:16:57 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 10:35:58 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	has_died(t_philo *philo, t_party *party, int time_to_die)
{
	unsigned long	timestamp;

	if (philo->eating_rn == 1)
		return (0);
	timestamp = get_time();
	if ((timestamp - philo->last_meal) >= (unsigned long) time_to_die)
	{
		log_state_change(philo, DIED);
		change_party_on_via_mutex(party, 0);
		pthread_mutex_unlock(&philo->philo_lock);
		return (1);
	}
	return (0);
}

int	must_close_party(t_party *party)
{
	int	i;
	int	must_eat_done;

	i = 0;
	must_eat_done = 1;
	while (i < party->input->num_philos)
	{
		pthread_mutex_lock(&party->philos[i]->philo_lock);
		if (has_died(party->philos[i], party, party->input->time_to_die))
			return (1);
		if (party->input->must_eat != -1)
		{
			if (party->philos[i]->meals_count < party->input->must_eat)
				must_eat_done = 0;
		}
		pthread_mutex_unlock(&party->philos[i]->philo_lock);
		i++;
	}
	if (must_eat_done == 1 && party->input->must_eat != -1)
	{
		change_party_on_via_mutex(party, 0);
		return (1);
	}
	return (0);
}

void	*close_party(void *param)
{
	t_party	*party;

	party = (t_party *) param;
	if (party->input->must_eat == 0)
		return (NULL);
	while (1)
	{
		if (must_close_party(party))
			return (NULL);
		delay(1);
	}
	return (NULL);
}
