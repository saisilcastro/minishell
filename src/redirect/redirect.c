/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:05:10 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/28 21:09:35 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	does_child(t_minishell *set)
{
	if (set->fd_in >= 0)
	{
		dup2(set->fd_in, STDIN_FILENO);
		close(set->fd_in);
	}
	if (set->fd_out >= 0)
	{
		dup2(set->fd_out, STDOUT_FILENO);
		close(set->fd_out);
	}
	else if (set->fd_out_p >= 0)
	{
		dup2(set->fd_out_p, STDOUT_FILENO);
		close(set->fd_out_p);
	}
}

static int	command_exec(t_minishell *set, t_command *cmd, char *path)
{
	int			pid;
	char		**arg;

	arg = NULL;
	if (count_args(cmd) >= 1)
	{
		arg = (char **)malloc((count_args(cmd) + 1) * sizeof(char *));
		if (!arg)
			return (-1);
		redirect_argument_get(cmd, &arg);
	}
	pid = fork();
	if (pid == 0)
	{
		does_child(set);
		if (execve(path, arg, __environ) == -1)
			return (127);
	}
	else
		waitpid(pid, &set->status, 0);
	if (WEXITSTATUS(set->status))
		set->status = WEXITSTATUS(set->status);
	free_arr(arg);
	return (0);
}

static void	redirect_execute(t_minishell *set, t_command *list, t_command *cmd)
{
	char		path[4096];

	if (set->fd_in < 0 && set->fd_in_p < 0
		&& set->fd_out < 0 && set->fd_out_p < 0)
		return ;
	if (shell_index(set, &cmd, Off) >= 4)
		builtin_execute(set, list, shell_index(set, &cmd, Off), cmd->name);
	else if ((search_path(set->path, cmd, path) && !access(path, F_OK)))
		set->status = command_exec(set, list, path);
	else
	{
		if (access(cmd->name, F_OK) < 0)
		{
			error(": command not found\n", cmd->name, 2);
			set->status = 127;
			return ;
		}
		set->status = command_exec(set, list, cmd->name);
		if (set->fd_out_p >= 0)
			close(set->fd_out_p);
		if (set->status == 2)
			set->status = 130;
	}
}

void	shell_redirect(t_minishell *set, t_command *cmd)
{
	t_command	*command;

	command = NULL;
	if (!valid_redirect(cmd))
	{
		set->status = 2;
		return ;
	}
	if (!open_redirects(set, cmd))
		return ;
	if (set->status != 130)
		command = has_command(cmd);
	if (command)
		redirect_execute(set, cmd, command);
	close_fds(set);
	set->flag = Off;
}
