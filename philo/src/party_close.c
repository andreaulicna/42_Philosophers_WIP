/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:16:57 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 13:57:23 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

/**
 * @brief	Checks if a philosopher has exceeded the specified time to die
 * without eating. It logs the death if necessary.
 * 
 * The philo_lock needs to be unlocked if the second if condition is true as
 * the function was entered with it being locked and hence the unlock
 * in the calling function won't be reached.
 *
 * @param	philo		a philo struct
 * @param	party		overall simulation structure
 * @param	time_to_die	time allowed for a philo to go without eating
 * @return	1 if the philosopher has died, 0 otherwise
 */
static int	has_died(t_philo *philo, t_party *party, int time_to_die)
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

/**
 * @brief	Determines whether the party should be closed.
 *
 * This function checks if the party should be closed based on two conditions:
 * if any philosopher has died 
 * OR if all philosophers reached the specified number of meals they must eat.
 *
 * @param	party	overall simulation structure
 * @return	1 		if the simulation should be closed, 0 otherwise
 */
static int	must_close_party(t_party *party)
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

/**
 * @brief Function executed by the monitoring thread.
 *
 * The function continuously checks if the simulation should be closed and does
 * so if a condition for closing is met.
 *
 * @param param Pointer to the party structure.
 * @return NULL once the party is closed.
 */
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
