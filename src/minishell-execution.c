/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:54:37 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/28 15:46:22 by lde-cast         ###   ########.fr       */
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

static t_status	shell_exec(t_minishell *set, char *path, char **arg, int *fd)
{
	int	pid;

	signal(SIGINT, shell_execute_ctrl_c);
	pid = fork();
	if (pid == 0)
	{
		dup2(*(fd + 1), STDOUT_FILENO);
		close(*(fd + 0));
		close(*(fd + 1));
		if (execve(path, arg, __environ) == -1)
			return (Off);
	}
	close(fd[1]);
	waitpid(pid, &set->status, 0);
	if (WEXITSTATUS(set->status))
		set->status = WEXITSTATUS(set->status);
	else if (set->status == 2)
		set->status = 130;
	return (On);
}

t_status	check_permission(t_minishell *set, char *path)
{
	if (access(path, F_OK))
	{
		error (" : command not found", path, 2);
		set->status = 127;
		return (Off);
	}
	if (!access(path, F_OK) && access(path, X_OK) != 0)
	{
		error (" : permission denied", path, 2);
		set->status = 126;
		return (Off);
	}
	return (On);
}

void	shell_run(t_minishell *set)
{
	int		fd[2];
	char	**arg;
	char	path[4096];

	ms_memset(path, '\0', 4096);
	argument_get(set->cmd, &arg);
	pipe(fd);
	if (search_path(set->path, set->cmd, path))
	{
		if (check_permission(set, path) && !shell_exec(set, path, arg, &fd[1]))
		{
			error(" : command not found", set->cmd->name, 2);
			exit(127);
		}
	}
	else
	{
		if (check_permission(set, set->cmd->name) && (access(set->cmd->name,
					F_OK) || !shell_exec(set, set->cmd->name, arg, &fd[1])))
		{
			error(": command not found", set->cmd->name, 2);
			exit(127);
		}
	}
	free_arr(arg);
}
