/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:07:11 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 13:59:08 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

/**
 * @brief	Fetches the current system time and returns it in milliseconds.
 *
 * @return	current time in milliseconds
 */
unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/**
 * @brief	Delays execution for a specified duration.
 *
 * The function is used when a thread needs to be delayed.
 *
 * @param	delay_by	duration to delay execution by
 */
void	delay(int delay_by)
{
	unsigned long	delay_start;

	delay_start = get_time();
	while (get_time() - delay_start < (unsigned long) delay_by)
		usleep(1);
}
