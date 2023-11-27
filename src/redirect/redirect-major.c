/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-major.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:06:27 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/27 13:50:23 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	command_execute(t_command *cmd, char ***arg, char *path, int fd)
{
	int		pid;

	if (access(path, F_OK) < 0)
	{
		ms_putstr_fd(path, 2);
		ms_putstr_fd(": command not found\n", 2);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		redirect_argument_get(cmd, arg, ">");
		dup2(fd, STDOUT_FILENO);
		if (execve(path, *arg, __environ) == -1)
		{
			close(fd);
			ms_putstr_fd(path, 2);
			ms_putstr_fd(": command not found\n", 2);
			return (127);
		}
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

static void	is_third_command(t_minishell *set)
{
	int		fd;
	char	path[4096];
	char	**arg;

	fd = open(set->cmd->next->name, O_WRONLY | O_CREAT | O_TRUNC, 00700);
	if (fd == -1)
		return ;
	if (!set->cmd->next->next)
		write(fd, "\0", 1);
	else
	{
		if (search_path(set->path, set->cmd->next->next, path))
		{
			set->status = command_execute(set->cmd, &arg, path, fd);
		}
		else
			set->status = command_execute(set->cmd,
					&arg, set->cmd->next->next->name, fd);
	}
	close(fd);
}

static void	first_execute(t_minishell *set, char *path)
{
	char		**arg;
	int			fd;

	fd = open(redirect_file(set->cmd, ">")->name,
			O_WRONLY | O_CREAT | O_TRUNC, 00700);
	if (fd == -1)
		return ;
	set->status = command_execute(set->cmd, &arg, path, fd);
	close(fd);
}

static void	first_command(t_minishell *set)
{
	char		path[4096];

	if (shell_index(set, set->cmd, Off) >= 4)
		builtin_execute(set, shell_index(set, set->cmd, Off), ">");
	else if (search_path(set->path, set->cmd, path))
		first_execute(set, path);
	else
		first_execute(set, set->cmd->name);
}

void	shell_redirect_major(t_minishell *set)
{
	if (set->cmd->next)
	{
		if (!ms_strncmp(set->cmd->name, ">", 1))
			is_third_command(set);
		else
			first_command(set);
	}
}
