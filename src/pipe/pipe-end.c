/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:15:28 by lumedeir          #+#    #+#             */
/*   Updated: 2024/01/08 11:52:02 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pipe_execute(t_minishell *set, char *path)
{
	char	**arg;

	close(set->fd_out_p);
	argument_get(set->pipe, &arg);
	if (!access(path, F_OK))
	{
		dup2(set->fd_in_p, STDIN_FILENO);
		close(set->fd_in_p);
		if (execve(path, arg, __environ) < 0)
		{
			free_arr(arg);
			return ;
		}
	}
	else
	{
		dup2(set->fd_in_p, STDIN_FILENO);
		close(set->fd_in_p);
		if (execve(set->pipe->name, arg, __environ) < 0)
		{
			free_arr(arg);
			return ;
		}
	}
}

static t_status	pipe_redirect_builtin_exec(t_minishell *set)
{
	int	i;

	i = shell_index(set, &set->pipe, On);
	if (i == 0 || shell_index(set, &set->pipe, Off) >= 4)
	{
		if (i == 0)
		{
			set->fd_in = set->fd_in_p;
			shell_redirect(set, set->pipe);
		}
		else
		{
			close(set->fd_in_p);
			if (i - 4 == 6)
				return (On);
			set->builtin[i - 4](set, set->pipe, 1);
		}
		return (On);
	}
	return (Off);
}

t_status	pipe_end(t_minishell *set)
{
	char	path[65535];

	if (set->fd_out_p >= 0)
		close(set->fd_out_p);
	if (set->fd_out >= 0)
		close(set->fd_out);
	set->last_pipe = On;
	if (pipe_redirect_builtin_exec(set))
		return (On);
	search_path(set->path, set->pipe, path);
	if (access(path, F_OK) && (access(set->pipe->name, F_OK)
			|| access(set->pipe->name, X_OK)))
	{
		close_fds(set);
		return (set->status = 127, Off);
	}
	signal(SIGINT, shell_execute_ctrl_c);
	pid_next_last(&set->pid, pid_push(fork()));
	if (pid_last(set->pid)->id == 0)
		pipe_execute(set, path);
	if (set->fd_in_p)
		close(set->fd_in_p);
	return (On);
}
