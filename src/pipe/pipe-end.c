/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 13:15:28 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/15 20:50:50 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_buffer(int fd)
{
	char	buffer[65535];
	int		byte;

	byte = read(fd, buffer, 65535);
	ms_putstr_fd(buffer, 2);
}

static void	pipe_execute(t_minishell *set, int pid, char *path)
{
	char	**arg;

	if (!access(path, F_OK))
	{
		argument_get(set->pipe, &arg);
		dup2(set->fd_in_p, STDIN_FILENO);
		close(set->fd_in_p);
		if (execve(path, arg, __environ) < 0)
			return ;
	}
	else
	{
		argument_get(set->pipe, &arg);
		dup2(set->fd_in_p, STDIN_FILENO);
		close(set->fd_in_p);
		if (execve(set->pipe->name, arg, __environ) < 0)
			return ;
	}
	close(set->fd_in_p);
}

static t_status	pipe_redirect_builtin_exec(t_minishell *set)
{
	int	i;
	int	j;

	i = shell_index(set, &set->pipe, On);
	j = shell_index(set, &set->pipe, Off);
	if (i == 0 || j >= 4)
	{
		if (i == 0)
			shell_redirect(set, set->pipe);
		else
		{
			dup2(set->fd_in_p, STDIN_FILENO);
			close(set->fd_in_p);
			set->builtin[i - 4](set, set->pipe, 1);
		}
		return (On);
	}
	set->status = 127;
	return (Off);
}

t_status	pipe_end(t_minishell *set)
{
	char	path[65535];
	int		pid;

	if (pipe_redirect_builtin_exec(set))
		return (On);
	search_path(set->path, set->pipe, path);
	if (access(path, F_OK) && access(set->pipe->name, F_OK))
		return (set->status = 127, Off);
	pid = fork();
	if (pid == 0)
		pipe_execute(set, pid, path);
	else
		waitpid(pid, NULL, 0);
	close(set->fd_in_p);
	return (On);
}
