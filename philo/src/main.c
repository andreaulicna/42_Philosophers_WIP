/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:03:10 by aulicna           #+#    #+#             */
/*   Updated: 2023/11/08 14:47:59 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

void	init_party(t_party *party, t_input *input)
{
	party->input = input;
	party->philos = (t_philo *) malloc(sizeof(t_philo) * input->num_philos);
}

int	main(int argc, char **argv)
{
	t_input	input;
	t_party	party;

	if (argc == 5 || argc == 6)
	{
		check_input_for_numbers(argc, argv);
		read_input(&input, argc, argv);
		init_party(&party, &input);
	}
	else
		printf("Input error: Wrong number of arguments received.\n");
	return (0);
}