/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-double-major.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:07:33 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/21 16:11:23 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	file_replacer(char *path)
{
	int	fd;

	fd = open(path, O_APPEND | O_CREAT | O_TRUNC, 00700);
	if (fd == -1)
		return ;
	write(fd, "\0", 1);
	close(fd);
}

static void	fork_process(t_minishell *set, char *path)
{
	int			pid;
	char		**arg;
	int			fd;

	pid = fork();
	if (pid == 0)
	{
		fd = open(set->cmd->next->next->name,
				O_WRONLY | O_APPEND | O_CREAT, 00700);
		dup2(fd, STDOUT_FILENO);
		argument_get(set->cmd->next->next->next, &arg);
		if (execve(path, arg, __environ) == -1)
		{
			set->status = 127;
			ms_putstr_fd("command not found", 2);
		}
		close(fd);
	}
}

static void	file_in_execute(t_minishell *set)
{
	char		path[4096];

	if (!set->cmd->next->next)
	{
		printf("syntax error near unexpected token `newline'\n");
		return ;
	}
	if (search_path(set->path, set->cmd, path))
		fork_process(set, path);
	else
		fork_process(set, set->cmd->name);
}

void	shell_redirect_double_major(t_minishell *set)
{
	if (!ms_strncmp(set->cmd->name, ">>", 2))
		file_replacer(set->cmd->next->name);
	if (!ms_strncmp(set->cmd->next->name, ">>", 2))
		file_in_execute(set);
}
