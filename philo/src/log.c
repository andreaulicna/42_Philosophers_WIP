/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:28:31 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 12:06:42 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

char	*get_state_change(t_state state)
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

char	*get_printf_format(t_state state)
{
	if (state == EAT)
		return ("\e[90m%-10lu\e[m \e[3m%-2d \e[1m%s\e[m\n");
	else if (state == SLEEP)
		return ("\e[90m%-10lu\e[m \e[3m%-2d \e[32m%s\e[m\n");
	else if (state == THINK)
		return ("\e[90m%-10lu\e[m \e[3m%-2d \e[33m%s\e[m\n");
	else if (state == LEFT_FORK || RIGHT_FORK)
		return ("\e[90m%-10lu\e[m \e[3m%-2d \e[34m%s\e[m\n");
}

void	log_state_change(t_philo *philo, t_state state)
{
	if (!continue_run_party(philo->party))
		return ;
	pthread_mutex_lock(&philo->mutexes->log);
	printf(get_printf_format(state), get_time() - philo->input->meet,
		philo->id + 1, get_state_change(state));
	pthread_mutex_unlock(&philo->mutexes->log);
}
