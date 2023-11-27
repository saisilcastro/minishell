/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-double-major.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:07:33 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/27 14:11:21 by lumedeir         ###   ########.fr       */
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
		redirect_argument_get(cmd, arg, ">>");
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

static void	redirect_execute(t_minishell *set, t_command *cmd, int fd)
{
	char		**arg;
	char		path[4096];

	if (shell_index(set, cmd, Off) >= 4)
	{
		if (!open_fd(&fd, ">>", redirect_file(set->cmd, ">>")->name, set))
			return ;
		builtin_execute(set, shell_index(set, cmd, Off), ">>", fd);
	}
	else if ((search_path(set->path, cmd, path) && !access(path, F_OK)))
		set->status = command_execute(cmd, &arg, path, fd);
	else
		set->status = command_execute(cmd, &arg, cmd->name, fd);
}

void	shell_redirect_double_major(t_minishell *set)
{
	t_command	*file;
	int			fd;

	file = redirect_file(set->cmd, ">>");
	if (!file || !open_fd(&fd, ">>", file->name, set))
		return ;
	if (set->cmd->next)
	{
		if (!ms_strncmp(set->cmd->name, ">>", 2))
			redirect_execute(set, file->next, fd);
		else
			redirect_execute(set, set->cmd, fd);
	}
}
