/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:07:11 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/30 09:44:10 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void	delay(int delay_by)
{
//	usleep (delay_by * 1000);
	unsigned long	delay_end;

	delay_end = get_time() + (unsigned long) delay_by;
	while (get_time() < delay_end)
		usleep(1);
}
