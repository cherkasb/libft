/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:40:27 by bcherkas          #+#    #+#             */
/*   Updated: 2018/11/14 20:24:20 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <sys/wait.h>

int			ft_pclose(int fd, int pid)
{
	int		piderr;
	int		fderr;

	piderr = waitpid(pid, &pid, 0);
	fderr = close(fd);
	if (piderr < 0 || fderr < 0)
		return (-1);
	return (0);
}
