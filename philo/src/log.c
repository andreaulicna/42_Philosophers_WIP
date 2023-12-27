/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:28:31 by aulicna           #+#    #+#             */
/*   Updated: 2023/12/27 22:04:14 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incl/philosophers.h"

char    *get_state_change(t_state state)
{
    if (state == LEFT_FORK || state == RIGHT_FORK)
        return ("has taken a fork");
    else if (state == EAT)
        return ("is eating");
    else if (state == SLEEP)
        return ("is sleeping");
    else if (state == THINK)
        return ("is thinking");
    else
        return ("died");
}

void    log_state_change(t_philo *philo, t_state state)
{
    int timestamp;

    timestamp = get_time() - philo->input->meet;
    pthread_mutex_lock(&philo->mutexes->log);
	printf("%-5i %-1d %s\n", timestamp, philo->id + 1, get_state_change(state));
    pthread_mutex_unlock(&philo->mutexes->log);
}