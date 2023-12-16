/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-begin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:15:07 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/15 20:16:13 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pipe_execute(t_minishell *set, int pid, char *path, int *fd)
{
	char	**arg;

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
			set->fd_out_p = fd[1];
			shell_redirect(set, set->pipe);
		}
		else
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			set->builtin[i - 4](set, set->pipe, 1);
		}
		close(set->fd_out_p);
		set->fd_in_p = fd[0];
		return (On);
	}
	close(fd[1]);
	set->fd_in_p = fd[0];
	set->status = 127;
	return (Off);
}

t_status	pipe_begin(t_minishell *set)
{
	char	path[65535];
	int		fd[2];
	int		pid;

	if (pipe(fd) < 0)
		return (Off);
	if (pipe_redirect_builtin_exec(set, fd))
		return (On);
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
	close(fd[1]);
	set->fd_in_p = fd[0];
	return (On);
}