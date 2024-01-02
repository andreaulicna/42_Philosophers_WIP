/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_change.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:12:08 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 10:20:45 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	change_party_on_via_mutex(t_party *party, int value)
{
	pthread_mutex_lock(&party->party_on_lock);
	party->party_on = value;
	pthread_mutex_unlock(&party->party_on_lock);
}

void	change_meals_count_via_mutex(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->philo_lock);
}

void	change_last_meal_via_mutex(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->philo_lock);
}
