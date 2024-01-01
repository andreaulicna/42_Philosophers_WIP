/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:03:10 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/01 21:18:25 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

void	only_one_philo(t_input *input)
{
	input->meet = get_time();
	printf("%lu %d %s\n", get_time() - input->meet, 1,
		get_state_change(LEFT_FORK));
	delay(input->time_to_die);
	printf("%lu %d %s\n", get_time() - input->meet, 1,
		get_state_change(DIED));
	exit(0);
}

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

void	*run_party(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	if (philo->input->must_eat == 0)
		return (NULL);
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

int	has_died(t_philo *philo)
{
	unsigned long	timestamp;
	
	if (philo->eating_rn == 1)
		return (0);
	timestamp = get_time();
	if ((timestamp - philo->last_meal) >= (unsigned long) philo->input->time_to_die)
	{
		log_state_change(philo, DIED);
		pthread_mutex_lock(&philo->party->party_on_lock);
		philo->party->party_on = 0;
		pthread_mutex_unlock(&philo->party->party_on_lock);
		pthread_mutex_unlock(&philo->philo_lock);
		return (1);
	}
	return (0);
}

int	must_close_party(t_party *party)
{
	int	i;
	int	must_eat_done;

	i = 0;
	must_eat_done = 1;
	while (i < party->input->num_philos)
	{
		pthread_mutex_lock(&party->philos[i]->philo_lock);
		if (has_died(party->philos[i]))
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
		pthread_mutex_lock(&party->party_on_lock);
		party->party_on = 0;
		pthread_mutex_unlock(&party->party_on_lock);
		return (1);
	}
	return (0);
}

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
		usleep(1000);
	}
	
	return (NULL);
}

int	start_party(t_party *party)
{
	int	i;

	party->input->meet = get_time();
	i = 0;
	while(i < party->input->num_philos)
	{
		if (pthread_create(&party->philos[i]->thread, NULL, &run_party,
				party->philos[i]))
			return (error(ERROR_THREAD, party));
		pthread_mutex_lock(&party->philos[i]->philo_lock);
		party->philos[i]->last_meal = party->input->meet;
		pthread_mutex_unlock(&party->philos[i]->philo_lock);
		i++;
	}
	if (pthread_create(&party->thread, NULL, &close_party, party))
			return (error(ERROR_THREAD, party));
	return (EXIT_SUCCESS);
}

int end_party(t_party *party)
{
	int	i;

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
		if (start_party(&party))
			return (EXIT_FAILURE);
		end_party(&party);
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