/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   party_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:16:20 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 13:59:21 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"
/**
 * @brief	Simulates the scenario when there is only one philosopher.
 *
 * @param	input		input structure containing simulation parameters
 */
static void	*only_one_philo(t_philo *philo)
{
	log_state_change(philo, LEFT_FORK);
	delay(philo->input->time_to_die);
	log_state_change(philo, DIED);
	return (NULL);
}

/**
 * @brief	Checks if the simulation should continue running or has finished.
 *
 * The status is checked by inspecting the 'party_on' flag within the party
 * structure.
 *
 * @param	party	overall simulation structure
 * @return	1 if the simulation should continue, 0 if it has finished.
 */
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

/**
 * @brief 	Function executed by each philosopher thread.
 *
 * This function represents the behavior of each philosopher during
 * the simulation. It decides when a philo should eat, sleep, and think.
 *
 * @param	param	a philo struct
 * @return	BULL	once the philosopher finishes their actions
 */
void	*run_party(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	if (philo->input->must_eat == 0)
		return (NULL);
	if (philo->input->num_philos == 1)
		return (only_one_philo(philo));
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
