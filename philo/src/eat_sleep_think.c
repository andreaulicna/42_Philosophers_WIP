/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:22:36 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/29 13:50:28 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

void    philo_lock(t_philo *philo)
{
    pthread_mutex_lock(&philo->philo_lock);
    printf("hej\n");
    philo->meals_count++;
    pthread_mutex_unlock(&philo->philo_lock);
}

void    philo_lost_last_meal(t_philo *philo)
{
    pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->philo_lock);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutexes->forks[philo->left_fork]);
    printf("locked fork: %d\n", philo->left_fork);
	log_state_change(philo, LEFT_FORK);
	pthread_mutex_lock(&philo->mutexes->forks[philo->right_fork]);
    printf("locked fork: %d\n", philo->right_fork);
	log_state_change(philo, RIGHT_FORK);
	log_state_change(philo, EAT);
    philo_lost_last_meal(philo);
	delay(philo, philo->input->time_to_eat);
	if (continue_run_party(philo))
    {
        printf("tu\n");
        philo_lock(philo);
        printf("tu\n");
    }
	pthread_mutex_unlock(&philo->mutexes->forks[philo->left_fork]);
    printf("unlocked fork: %d\n", philo->left_fork);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->right_fork]);
    printf("unlocked fork: %d\n", philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	log_state_change(philo, SLEEP);
	delay(philo, philo->input->time_to_sleep);
}

void	philo_think(t_philo *philo, int log)
{
	time_t	time_to_check;
	time_t	time_to_think;

    pthread_mutex_lock(&philo->philo_lock);
    time_to_check = (philo->input->time_to_die - (get_time() - philo->last_meal)
		- philo->input->time_to_eat) / 2;
    pthread_mutex_unlock(&philo->philo_lock);
	if (time_to_check > 500)
		time_to_think = 200;
	else
		time_to_think = 1;
	if (log)
		log_state_change(philo, THINK);
	delay(philo, time_to_think);
}
