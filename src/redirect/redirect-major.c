/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-major.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:06:27 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/22 13:33:18 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	command_execute(t_command *cmd, char ***arg, char *path, int fd)
{
	int		pid;

	if (access(path, F_OK) == -1)
	{
		ms_putstr_fd(path, 2);
		ms_putstr_fd(": command not found\n", 2);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		argument_get(cmd, arg);
		if (execve(path, *arg, __environ) == -1)
		{
			close(fd);
			ms_putstr_fd(path, 2);
			ms_putstr_fd(": command not found\n", 2);
			return (127);
		}
	}
	return (0);
}

static void	is_third_command(t_minishell *set)
{
	int		fd;
	int		pid;
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
			set->status = command_execute(set->cmd->next->next->next,
					&arg, path, fd);
		}
		else
			set->status = command_execute(set->cmd->next->next->next,
					&arg, set->cmd->next->next->name, fd);
	}
	close(fd);
}

static void	first_execute(t_minishell *set, char *path)
{
	int			pid;
	char		**arg;
	int			fd;

	fd = open(set->cmd->next->next->name,
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return ;
	set->status = command_execute(set->cmd->next->next->next, &arg, path, fd);
	close(fd);
}

static void	first_command(t_minishell *set)
{
	char		path[4096];

	if (!set->cmd->next->next)
	{
		printf("syntax error near unexpected token `newline'\n");
		return ;
	}
	if (search_path(set->path, set->cmd, path))
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
		else if (!ms_strncmp(set->cmd->next->name, ">", 1))
			first_command(set);
	}
}
