/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-begin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:15:07 by lumedeir          #+#    #+#             */
/*   Updated: 2024/01/08 11:51:11 by lde-cast         ###   ########.fr       */
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
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(path, arg, __environ) < 0)
			return ;
	}
	else
	{
		argument_get(set->pipe, &arg);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (execve(set->pipe->name, arg, __environ) < 0)
			return ;
	}
}

void	print_buffer(int fd)
{
	char	c;

	while (read(fd, &c, 1) && c != EOF)
		write(2, &c, 1);
}

static t_status	pipe_redirect_builtin_exec(t_minishell *set, int *fd)
{
	int	i;

	i = shell_index(set, &set->pipe, On);
	if (i == 0 || shell_index(set, &set->pipe, Off) >= 4)
	{
		if (i == 0)
		{
			set->fd_out = fd[1];
			shell_redirect(set, set->pipe);
		}
		else
		{
			close(set->fd_in_p);
			if (i - 4 == 6)
				return (On);
			set->builtin[i - 4](set, set->pipe, fd[1]);
		}
		if (fd[1] >= 0)
			close(fd[1]);
		set->fd_in_p = fd[0];
		return (On);
	}
	return (Off);
}

t_status	pipe_begin(t_minishell *set)
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
		close(fd[1]);
		set->fd_in_p = fd[0];
		return (set->status = 127, Off);
	}
	signal(SIGINT, shell_execute_ctrl_c);
	pid_next_last(&set->pid, pid_push(fork()));
	if (pid_last(set->pid)->id == 0)
		pipe_execute(set, path, fd);
	if (fd[1] >= 0)
		close(fd[1]);
	set->fd_in_p = fd[0];
	return (On);
}
