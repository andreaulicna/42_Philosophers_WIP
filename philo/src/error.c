/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulicna <aulicna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:54:45 by aulicna           #+#    #+#             */
/*   Updated: 2024/01/02 13:54:39 by aulicna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

/**
 * @brief	Prints a string in the specified file descriptor.
 * 
 * @param	char*	string to print
 * @param	fd		file descriptor to print to
*/
static void	ft_putstr_fd(char *s, int fd)
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

/**
 * @brief	Prints an error message based on the error encountered.
 * 
 * @param	error	error encountered
 * @param	party	overall simulation structure
*/
int	error(int error, t_party *party)
{
	if (error == ERROR_MALLOC)
		ft_putstr_fd("Error: Encountered memory allocation error.\n", 2);
	else if (error == ERROR_MUTEX)
		ft_putstr_fd("Error: Encountered mutex creation error.\n", 2);
	else if (error == ERROR_THREAD)
		ft_putstr_fd("Error: Encountered thread creation error.\n", 2);
	return (error);
}
