/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:03:10 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/27 22:05:19 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

void	delay(int delay_by)
{
	int end_delay_at;

	end_delay_at = get_time() + delay_by;
	while (get_time() < end_delay_at)
		usleep(1); 
//	unsigned long	start_time;
//
//	start_time = get_time();
//	while (get_time() - start_time < (unsigned long)delay_by)
//		usleep(10);
}

void	only_one_philo(t_input *input)
{
	int	timestamp;
	
	delay(input->time_to_die);
	//usleep(input->time_to_sleep * 1000);
    timestamp = get_time_to_print(input->meet);
	printf("%-5i %-1d %s\n", timestamp, 1, get_state_change(DIED));
	exit(0);
}

void	philo_sleep(t_philo *philo)
{
	log_state_change(philo, SLEEP);
	delay(philo->input->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	log_state_change(philo, THINK);
	philo->alive = 1;
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutexes->forks[philo->left_fork]);
	log_state_change(philo, LEFT_FORK);
	pthread_mutex_lock(&philo->mutexes->forks[philo->right_fork]);
	log_state_change(philo, RIGHT_FORK);
	log_state_change(philo, EAT);
	philo->last_meal = get_time();
	delay(philo->input->time_to_eat);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->right_fork]);
}

void	*run_party(void *param)
{
	t_philo	*philo;
	int	i;

	philo = (t_philo *) param;
	if (philo->input->must_eat == 0)
		return (NULL);
	philo->last_meal = philo->input->meet;
	if (philo->id % 2 == 0)
		philo_eat(philo);
	i = 0;
	while (philo->alive != 1)
	{
		philo_think(philo);
		philo_eat(philo);
		philo_sleep(philo);
		i++;
	}
	return (NULL);
}

int	start_party(t_party *party)
{
	int	i;

	i = 0;
	party->input->meet = get_time();
	while(i < party->input->num_philos)
	{
		party->philos[i]->last_meal = get_time();
		if (pthread_create(&party->philos[i]->thread, NULL, &run_party,
				party->philos[i]))
			return (error(ERROR_THREAD, party));
		i++;
	}
//	if (pthread_create(&party->thread, NULL, &close_party, party))
//			return (error(ERROR_THREAD, party));
	return (EXIT_SUCCESS);
}

int handle_party(t_party *party)
{
	int	j;

	start_party(party);
	j = 0;
	while (j < party->input->num_philos)
	{
		pthread_join(party->philos[j]->thread, NULL);
		j++;
	}
	pthread_mutex_destroy(&party->mutexes->log);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_input	input;
	t_mutex	mutexes;
	t_party	party;

	if (argc == 5 || argc == 6)
	{
		check_input_for_numbers(argc, argv);
		read_input(&input, argc, argv);
		if (input.num_philos == 1)
			only_one_philo(&input);
		if (init_mutexes(&mutexes, input.num_philos))
			return (EXIT_FAILURE);
		if (init_party(&party, &input, &mutexes))
			return (EXIT_FAILURE);
		handle_party(&party);
		free_party(&party);
	}
	else
	{
		printf("Input error: Wrong number of arguments received.\n\n");
		printf("Correct usage: ./philo number_of_philosophers time_to_die "
				"time_to_eat time_to_sleep " 
				"[number_of_times_each_philosopher_must_eat]\n\n");
	}
	return (EXIT_SUCCESS);
}