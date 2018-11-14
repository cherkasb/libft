/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcherkas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:40:27 by bcherkas          #+#    #+#             */
/*   Updated: 2018/11/14 19:47:40 by bcherkas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

static void	forked(char *const flags[], char *const env[], int pipefd[2], int mode)
{
	if (mode == W)
	{
		close(STDIN_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
	}
	else
	{
		close(STDOUT_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
	}
	execve(flags[0], flags, env);
	perror("ft_popen");
	exit(EXIT_FAILURE);
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
	{
		perror("fork");
		exit(-1);
	}
	if (!pid)
		forked(flags, env, pipefd, mode);
	waitpid(pid, &pid, 0);
	if (mode == R)
	{
		close(pipefd[1]);
		return (pipefd[0]);
	}
	close(pipefd[0]);
	return (pipefd[1]);
}
