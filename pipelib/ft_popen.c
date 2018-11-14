/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:40:27 by bcherkas          #+#    #+#             */
/*   Updated: 2018/11/14 17:17:49 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>

static void	forked(char const *command, char *const flags[], int pipefd[2])
{
	dup2(pipefd[0], 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	close(pipefd[1]);
	execve(command, flags, NULL);
	perror("ft_popen");
	exit(EXIT_FAILURE);
}

int			ft_popen(char const *command, char *const flags[], int mode)
{
	int		pipefd[2];
	pid_t	pid;

	if (mode != R && mode != W && pipe(pipefd) == -1)
		return (-1);
	if ((pid = fork()) < 0)
		return (-1);
	if (pid == 0)
		forked(command, flags, pipefd);
	else
		wait(EXIT_SUCCESS);
	if (mode == R)
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
	else if (mode == W)
	{
		close(pipefd[0]);
		return (pipefd[1]);
	}
	return (-1);
}
