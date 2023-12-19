/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:54:37 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/18 13:19:21 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <errno.h>

void	argument_get(t_command *cmd, char ***arg)
{
	t_command	*curr;
	int			i;

	*arg = (char **)malloc((count_args(cmd) + 1) * sizeof(char *));
	if (!arg || !*arg)
		return ;
	i = 0;
	curr = cmd;
	while (curr)
	{
		*(*arg + i++) = ms_strdup(curr->name);
		curr = curr->next;
	}
	*(*arg + i) = NULL;
}

static t_status	shell_execute(char *path, char **arg, int *fd, int mode)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (!mode)
			dup2(*(fd + 0), STDIN_FILENO);
		else
			dup2(*(fd + 1), STDOUT_FILENO);
		close(*(fd + 0));
		close(*(fd + 1));
		if (execve(path, arg, __environ) == -1)
			return (Off);
	}
	if (!mode)
	{
		close(fd[0]);
		close(fd[1]);
	}
	waitpid(pid, NULL, 0);
	return (On);
}

void	shell_run(t_minishell *set)
{
	int		fd[2];
	char	**arg;
	char	path[4096];

	argument_get(set->cmd, &arg);
	pipe(fd);
	if (search_path(set->path, set->cmd, path))
	{
		if (!shell_execute(path, arg, &fd[1], 1))
		{	
			error(" : command not found", set->cmd->name, 2);
			set->status = 127;
		}
	}
	else
	{
		if (access(set->cmd->name, F_OK)
			|| !shell_execute(set->cmd->name, arg, &fd[1], 1))
		{
			error(": command not found", set->cmd->name, 2);
			set->status = 127;
		}
	}
	free_arr(arg);
}
