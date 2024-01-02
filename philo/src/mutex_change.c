/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:12:08 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 15:32:43 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

/**
 * @brief	Changes the party_on flag to the specified value while holding
 * the part_on_lock mutex locked. 
 *
 * @param	party	overall simulation structure
 */
void	change_party_on_via_mutex(t_party *party, int value)
{
	pthread_mutex_lock(&party->party_on_lock);
	party->party_on = value;
	pthread_mutex_unlock(&party->party_on_lock);
}

/**
 * @brief	Increments the value of meals_count while holding the philo_lock 
 * mutex locked.
 *
 * @param	philo	a philo struct
 */
void	change_meals_count_via_mutex(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->philo_lock);
}

/**
 * @brief	Changes the last_meal timestamp to the current time 
 * while holding the philo_lock mutex locked.
 *
 * @param	philo	a philo struct
 */
void	change_last_meal_via_mutex(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->philo_lock);
}

/**
 * @brief	Changes the eating_rn flag for a philo to the specified value
 * while holding philo_lock mutex locked. 
 *
 * @param	party	overall simulation structure
 */
void	change_eating_rn_via_mutex(t_philo *philo, int value)
{
	pthread_mutex_lock(&philo->philo_lock);
	philo->eating_rn = value;
	pthread_mutex_unlock(&philo->philo_lock);
}
