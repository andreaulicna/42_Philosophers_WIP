/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:03:10 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/13 08:42:37 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	in_ms;

	gettimeofday(&time, NULL);
	in_ms = (time.tv_sec * 1000) + (time.tv_sec / 100);
	return (in_ms);
}

int	init_party(t_party *party, t_input *input)
{
	int	i;

	party->philos = (t_philo *) malloc(sizeof(t_philo) * input->num_philos);
	if (!party->philos)
		return (error('A'));
	i = 0;
	while (i < input->num_philos)
	{
		party->philos[i].thread = 
		party->philos[i].id = i;
		party->philos[i].meals_count = 0;
		party->philos[i].last_meal = 0;
		party->philos[i].right_fork = i;
		party->philos[i].left_fork = i + 1;
		if (party->philos[i].left_fork > input->num_philos)
			party->philos[i].left_fork = 1;
		i++;
	}
	party->meet = get_time();
	
	return (0);
}

void	only_one(t_input *input)
{
	usleep(input->time_to_die * 1000);
	printf("%-5d %-1d %s\n", input->time_to_die, input->num_philos, DIED);
	exit(0);
}

void	free_party(t_party *party)
{
	free(party->philos);
}

int	main(int argc, char **argv)
{
	t_input	input;
	t_party	party;

	if (argc == 5 || argc == 6)
	{
		check_input_for_numbers(argc, argv);
		read_input(&input, argc, argv);
		if (input.num_philos == 1)
			only_one(&input);
		init_party(&party, &input);
	}
	else
		printf("Input error: Wrong number of arguments received.\n");
	free_party(&party);
	return (0);
}