/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:07:11 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/27 22:00:25 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_sec / 1000));
}

int	get_time_to_print(int meet)
{
	return (get_time() - meet);
}

//unsigned long	get_time(void)
//{
//	struct timeval	time;
//	int	in_ms;
//
//	gettimeofday(&time, NULL);
//	in_ms = (time.tv_sec * 1000) + (time.tv_sec / 1000);
//	return (in_ms);
//}