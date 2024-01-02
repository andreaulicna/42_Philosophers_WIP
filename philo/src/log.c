/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:28:31 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 14:31:59 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

/**
 * @brief	Retrieves the correct value for the provided state code.
 *
 * @param	state	state from the t_state enum to retrieve value for
 * @return	char*	the value of the state to retrieve
 */

static char	*get_state_change(t_state state)
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

/**
 * @brief	Retrieves the correct formatting for printf in log_state_change 
 * based on the state provided.
 *
 * @param	state	state from the t_state enum to retrieve value for
 * @return	char*	the formatting the printf in log_state_change should use
 */
static char	*get_printf_format(t_state state)
{
	if (state == EAT)
		return ("\e[90m%-10lu\e[m \e[3m%-2d \e[1m%s\e[m\n");
	else if (state == SLEEP)
		return ("\e[90m%-10lu\e[m \e[3m%-2d \e[32m%s\e[m\n");
	else if (state == THINK)
		return ("\e[90m%-10lu\e[m \e[3m%-2d \e[33m%s\e[m\n");
	else if (state == LEFT_FORK || state == RIGHT_FORK)
		return ("\e[90m%-10lu\e[m \e[3m%-2d \e[34m%s\e[m\n");
	else
		return ("\e[90m%-10lu\e[m \e[3m%-2d \e[90m%s\e[m\n");
}

/**
 * @brief	Logs a philo's state change in the terminal. 
 * 
 * First it checks whether the simulation should keep running to avoid printing
 * a log after a previous death log.
 * 
 * Log mutex is used to ensure the printing from different threads
 * doesn't clash.
 *
 * @param	state	state from the t_state enum to retrieve value for
 * @return	char*	the formatting the printf in log_state_change should use
 */
void	log_state_change(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->mutexes->log);
	if (!continue_run_party(philo->party))
	{
		pthread_mutex_unlock(&philo->mutexes->log);
		return ;
	}
	printf(get_printf_format(state), get_time() - philo->input->meet,
		philo->id + 1, get_state_change(state));
	pthread_mutex_unlock(&philo->mutexes->log);
}
