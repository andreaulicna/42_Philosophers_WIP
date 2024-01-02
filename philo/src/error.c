/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:54:45 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 09:54:01 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	if (!s)
	{
		return ;
	}
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	error(int error, t_party *party)
{
	if (party)
		free_party(party);
	if (error == ERROR_MALLOC)
		ft_putstr_fd("Error: Encountered memory allocation error.\n", 2);
	else if (error == ERROR_MUTEX)
		ft_putstr_fd("Error: Encountered mutex creation error.\n", 2);
	else if (error == ERROR_THREAD)
		ft_putstr_fd("Error: Encountered thread creation error.\n", 2);
	return (error);
}
