/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:22:36 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 15:41:47 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

/**
 * @brief	Represents the eating behavior of a philosopher.
 * 
 * 1. The forks are locked either in 'left then right' or 'right then left'
 * fashion based on the philo's id being even or odd to avoid a deadlock.
 * 2. The eating_rn flag is set to 1. This helps to avoid a situation
 * of a philo dying just as eating is supposed to start.
 * 3. The eating state change is printed.
 * 4. The last_meal timestamp is updated to current time.
 * 5. The thread is delayed by the eating time.
 * 6. The eating process is finished by setting the eating_rn flag to 0,
 * incrementing the meals_count variable and unlocking both forks.
 *
 * @param	philo	a philo struct
 */
void	philo_eat(t_philo *philo)
{
	if (philo->id != 1)
	{
		pthread_mutex_lock(&philo->mutexes->forks[philo->left_fork]);
		log_state_change(philo, LEFT_FORK);
		change_eating_rn_via_mutex(philo, 1);
		pthread_mutex_lock(&philo->mutexes->forks[philo->right_fork]);
		log_state_change(philo, RIGHT_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->mutexes->forks[philo->right_fork]);
		log_state_change(philo, RIGHT_FORK);
		change_eating_rn_via_mutex(philo, 1);
		pthread_mutex_lock(&philo->mutexes->forks[philo->left_fork]);
		log_state_change(philo, LEFT_FORK);
	}
	log_state_change(philo, EAT);
	change_last_meal_via_mutex(philo);
	delay(philo->input->time_to_eat);
	change_eating_rn_via_mutex(philo, 0);
	if (continue_run_party(philo->party))
		change_meals_count_via_mutex(philo);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->left_fork]);
}

/**
 * @brief	Represents the sleeping behavior of a philosopher.
 *
 * The function delays the particular thread by the time_to_sleep.
 * 
 * @param	philo	a philo struct
 */
void	philo_sleep(t_philo *philo)
{
	log_state_change(philo, SLEEP);
	delay(philo->input->time_to_sleep);
}

/**
 * @brief	Represents the thinking behavior of a philosopher.
 *
 * The function prints the state change to thinking.
 *
 * @param	philo	a philo struct
 */
void	philo_think(t_philo *philo)
{
	log_state_change(philo, THINK);
}
