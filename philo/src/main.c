/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:03:10 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/28 22:58:21 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

void	only_one_philo(t_input *input)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	printf("%-5i %-1d %s\n", get_time_to_print(input->meet), 1,
		get_state_change(LEFT_FORK));
	usleep(input->time_to_die * 1000);
	gettimeofday(&now, NULL);
	printf("%-5i %-1d %s\n", get_time_to_print(input->meet), 1,
		get_state_change(DIED));
	exit(0);
}

void	philo_sleep(t_philo *philo)
{
	log_state_change(philo, SLEEP);
	delay(philo->input->time_to_sleep);
}

void	philo_think(t_philo *philo, int log)
{
	time_t	time_to_check;
	time_t	time_to_think;

    time_to_check = (philo->input->time_to_die - (get_time() - philo->last_meal)
		- philo->input->time_to_eat) / 2;
	if (time_to_check > 500)
		time_to_think = 200;
	else
		time_to_think = 1;
	if (log)
		log_state_change(philo, THINK);
	delay(time_to_think);
}

int	continue_run_party(t_philo *philo)
{
	int	signal;

	signal = 1;
	pthread_mutex_lock(&philo->mutexes->party_on);
	if (!philo->input->party_on)
		signal = 0;
	pthread_mutex_unlock(&philo->mutexes->party_on);
	return (signal);
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
	if (continue_run_party(philo))
		philo->meals_count += 1;
	pthread_mutex_unlock(&philo->mutexes->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->mutexes->forks[philo->right_fork]);
}

void	*run_party(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	if (philo->input->must_eat == 0)
		return ;
	if (philo->id % 2 != 0)
		philo_think(philo, 0);
	while (continue_run_party(philo))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo, 1);
	}
	return (NULL);
}

int	must_close_party(t_party *party)
{
	return (100);	
}

void	*close_party(void *param)
{
	t_party	*party;

	party = (t_party *) param;
	if (party->input->must_eat == 0)
		return ;
	pthread_mutex_lock(&party->mutexes->party_on);
	party->input->party_on = 1;
	pthread_mutex_unlock(&party->mutexes->party_on);
	while (1)
	{
		if (must_close_party(party))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

int	start_party(t_party *party)
{
	int	i;

	i = 0;
	while(i < party->input->num_philos)
	{
		party->philos[i]->last_meal = party->input->meet;
		if (pthread_create(&party->philos[i]->thread, NULL, &run_party,
				party->philos[i]))
			return (error(ERROR_THREAD, party));
		i++;
	}
	if (pthread_create(&party->thread, NULL, &close_party, party))
			return (error(ERROR_THREAD, party));
	return (EXIT_SUCCESS);
}

int handle_party(t_party *party)
{
	int	i;

	if(start_party(party))
		return (EXIT_FAILURE);
	i = 0;
	while (i < party->input->num_philos)
	{
		pthread_join(party->philos[i]->thread, NULL);
		i++;
	}
	pthread_join(party->thread, NULL);
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
		if (handle_party(&party))
			return (EXIT_FAILURE);
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