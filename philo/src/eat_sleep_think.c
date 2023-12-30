/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:22:36 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/30 21:19:55 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

void    change_meals_count_via_mutex(t_philo *philo)
{
    pthread_mutex_lock(&philo->philo_lock);
    philo->meals_count++;
    pthread_mutex_unlock(&philo->philo_lock);
}

void    change_last_meal_via_mutex(t_philo *philo, unsigned long timestamp)
{
    pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = timestamp;
    pthread_mutex_unlock(&philo->philo_lock);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutexes->forks[philo->left_fork]);
	log_state_change(philo, LEFT_FORK);
	pthread_mutex_lock(&philo->mutexes->forks[philo->right_fork]);
	log_state_change(philo, RIGHT_FORK);
	log_state_change(philo, EAT);
    change_last_meal_via_mutex(philo, get_time());
	delay(philo->input->time_to_eat);
	if (continue_run_party(philo->party))
        change_meals_count_via_mutex(philo);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->left_fork]);
}

void	philo_sleep(t_philo *philo)
{
	log_state_change(philo, SLEEP);
	delay(philo->input->time_to_sleep);
}

long    get_time_to_think(t_philo *philo)
{
	long	time_to_check;

    pthread_mutex_lock(&philo->philo_lock);
    time_to_check = (philo->input->time_to_die - (get_time() - philo->last_meal)
		- philo->input->time_to_eat) / 2;
    pthread_mutex_unlock(&philo->philo_lock);
	if (time_to_check > 500)
		return (200);
	else
		return(1);
}

void	philo_think(t_philo *philo)
{
    log_state_change(philo, THINK);
//	time_t	time_to_think;
//
//    time_to_think = get_time_to_think(philo);
//	if (log)
//		log_state_change(philo, THINK);
//	delay(time_to_think);
}
