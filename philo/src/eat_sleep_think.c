/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:22:36 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 10:20:53 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutexes->forks[philo->left_fork]);
	log_state_change(philo, LEFT_FORK);
	pthread_mutex_lock(&philo->philo_lock);
	philo->eating_rn = 1;
	pthread_mutex_unlock(&philo->philo_lock);
	pthread_mutex_lock(&philo->mutexes->forks[philo->right_fork]);
	log_state_change(philo, RIGHT_FORK);
	log_state_change(philo, EAT);
	change_last_meal_via_mutex(philo);
	delay(philo->input->time_to_eat);
	pthread_mutex_lock(&philo->philo_lock);
	philo->eating_rn = 0;
	pthread_mutex_unlock(&philo->philo_lock);
	if (continue_run_party(philo->party))
		change_meals_count_via_mutex(philo);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->right_fork]);
}

void	philo_sleep(t_philo *philo)
{
	log_state_change(philo, SLEEP);
	delay(philo->input->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	log_state_change(philo, THINK);
}
