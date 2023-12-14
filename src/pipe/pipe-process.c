/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:56:27 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/14 19:23:55 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pipe_begin(t_minishell *set)
{
	char	path[65535];
	char	**arg;
	int		fd[2];
	int		pid;

	if (pipe(fd) < 0)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (search_path(set->path, set->pipe, path))
		{
			argument_get(set->pipe, &arg);
			dup2(fd[1], STDOUT_FILENO);
			if (execve(path, arg, __environ) < 0)
			{
				set->status = 127;
				close(fd[1]);
				return ;
			}
		}
	}
	else
		waitpid(pid, NULL, 0);
	close(fd[1]);
	set->fd_in = fd[0];
}

void	pipe_between(t_minishell *set)
{
	char	path[65535];
	char	**arg;
	int		fd[2];
	int		pid;

	if (pipe(fd) < 0)
		return ;
	pid = fork();
	if (pid == 0)
	{
		if (search_path(set->path, set->pipe, path))
		{
			argument_get(set->pipe, &arg);
			dup2(set->fd_in, STDIN_FILENO);
			close(set->fd_in);
			dup2(fd[1], STDOUT_FILENO);
			if (execve(path, arg, __environ) < 0)
			{
				set->status = 127;
				return ;
			}
		}
	}
	else
		waitpid(pid, NULL, 0);
	close(set->fd_in);
	close(fd[1]);
	set->fd_in = fd[0];
}

void	pipe_end(t_minishell *set)
{
	char	path[65535];
	char	**arg;
	int		fd[2];
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		if (search_path(set->path, set->pipe, path))
		{
			argument_get(set->pipe, &arg);
			dup2(set->fd_in, STDIN_FILENO);
			close(set->fd_in);
			if (execve(path, arg, __environ) < 0)
			{
				set->status = 127;
				return ;
			}
		}
	}
	else
		waitpid(pid, NULL, 0);
	close_fds(set);
}
