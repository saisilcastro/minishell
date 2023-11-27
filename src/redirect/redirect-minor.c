/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-minor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:05:10 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/27 10:59:53 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	command_execute(t_command *cmd, char ***arg, char *path, int fd)
{
	int	pid;

	if (access(path, F_OK) < 0)
	{
		ms_putstr_fd(path, 2);
		ms_putstr_fd(": command not found\n", 2);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		argument_get(cmd, arg, "<");
		dup2(fd, STDIN_FILENO);
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

static void	redirect_execute(t_minishell	*set, t_command *cmd, int fd)
{
	char		**arg;
	char		path[4096];
	int			pid;

	if ((search_path(set->path, cmd, path) && !access(path, F_OK)))
		set->status = command_execute(cmd, &arg, path, fd);
	else
		set->status = command_execute(cmd, &arg, cmd->name, fd);
}

void	shell_redirect_minor(t_minishell *set)
{
	t_command	*file;
	int			fd;

	file = redirect_file(set->cmd, "<");
	fd = open(file->name, O_RDONLY, 0777);
	if (fd == -1)
	{
		ms_putstr_fd("minishell: ", 2);
		ms_putstr_fd(file->name, 2);
		ms_putstr_fd(": no such file or directory\n", 2);
	}
	if (!ms_strncmp(set->cmd->name, "<", 1))
		redirect_execute(set, file->next, fd);
	else
		redirect_execute(set, set->cmd, fd);
	close(fd);
}
