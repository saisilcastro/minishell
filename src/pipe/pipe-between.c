/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-between.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:15:21 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/15 15:52:43 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pipe_execute(t_minishell *set, int pid, char *path, int *fd)
{
	char	**arg;

	if (!access(path, F_OK))
	{
		argument_get(set->pipe, &arg);
		dup2(set->fd_in_p, STDIN_FILENO);
		close(set->fd_in_p);
		dup2(fd[1], STDOUT_FILENO);
		if (execve(path, arg, __environ) < 0)
			return ;
	}
	else
	{
		argument_get(set->pipe, &arg);
		dup2(set->fd_in_p, STDIN_FILENO);
		close(set->fd_in_p);
		dup2(fd[1], STDOUT_FILENO);
		if (execve(set->pipe->name, arg, __environ) < 0)
			return ;
	}
}

t_status	pipe_between(t_minishell *set)
{
	char	path[65535];
	int		fd[2];
	int		pid;

	if (pipe(fd) < 0)
		return (Off);
	search_path(set->path, set->pipe, path);
	if (access(path, F_OK) && access(set->pipe->name, F_OK))
	{
		close(fd[1]);
		set->fd_in_p = fd[0];
		return (set->status = 127, Off);
	}
	pid = fork();
	if (pid == 0)
		pipe_execute(set, pid, path, fd);
	else
		waitpid(pid, NULL, 0);
	close(set->fd_in_p);
	close(fd[1]);
	set->fd_in_p = fd[0];
	return (On);
}
