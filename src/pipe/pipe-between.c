/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-between.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:15:21 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/21 15:55:17 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pipe_execute(t_minishell *set, char *path, int *fd)
{
	char	**arg;

	close(fd[0]);
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

static t_status	pipe_redirect_builtin_exec(t_minishell *set, int *fd)
{
	int	i;
	int	j;

	i = shell_index(set, &set->pipe, On);
	j = shell_index(set, &set->pipe, Off);
	if (i == 0 || j >= 4)
	{
		if (i == 0)
		{
			set->fd_in = set->fd_in_p;
			set->fd_out_p = fd[1];
			shell_redirect(set, set->pipe);
			close(set->fd_in);
		}
		else
			set->builtin[i - 4](set, set->pipe, fd[1]);
		if (fd[1] >= 0)
			close(fd[1]);
		set->fd_in_p = fd[0];
		return (On);
	}
	return (Off);
}

t_status	pipe_between(t_minishell *set)
{
	char	path[65535];
	int		fd[2];

	if (pipe(fd) < 0)
		return (Off);
	if (pipe_redirect_builtin_exec(set, fd))
		return (On);
	search_path(set->path, set->pipe, path);
	if (access(path, F_OK) && (access(set->pipe->name, F_OK)
			|| access(set->pipe->name, X_OK)))
	{
		close(set->fd_in_p);
		close(fd[1]);
		set->fd_in_p = fd[0];
		return (set->status = 127, Off);
	}
	signal(SIGINT, shell_execute_ctrl_c);
	pid_next_last(&set->pid, pid_push(fork()));
	if (pid_last(set->pid)->id == 0)
		pipe_execute(set, path, fd);
	close(set->fd_in_p);
	close(fd[1]);
	set->fd_in_p = fd[0];
	return (On);
}
