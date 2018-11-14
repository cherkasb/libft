/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:40:27 by bcherkas          #+#    #+#             */
/*   Updated: 2018/11/14 20:22:35 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

static int	forked(char *const flags[], char *const env[], int pipefd[2], int mode)
{
	int		err;

	err = 0;
	if (mode == W)
	{
		err += close(STDIN_FILENO);
		if (dup2(pipefd[0], STDIN_FILENO) < 0)
			return (-1);
		err += close(pipefd[1]);
	}
	else
	{
		err += close(STDOUT_FILENO);
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			return (-1);
		err += close(pipefd[0]);
	}
	if (err < 0)
		return (-1);
	execve(flags[0], flags, env);
	return (-1);
}

int			ft_popen(char *const flags[], char *const env[], int mode)
{
	int		pipefd[2];
	pid_t	pid;

	if (!flags || !(mode == W || mode == R))
		return (-1);
	if (pipe(pipefd) < 0)
		return (-1);
	pid = fork();
	if (pid < 0)
		return(-1);
	if (!pid)
		if (forked(flags, env, pipefd, mode) < 0)
			return (-1);
	if (mode == R)
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
	close(pipefd[0]);
	return (pipefd[1]);
}
