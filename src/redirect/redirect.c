/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:05:10 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/07 15:28:00 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	command_exec(t_command *cmd, char *path, int fd_in, int fd_out)
{
	int			pid;
	char		**arg;

	arg = NULL;
	if (count_args(cmd) > 1)
	{
		arg = (char **)malloc((count_args(cmd) + 1) * sizeof(char *));
		if (!arg)
			return (-1);
		redirect_argument_get(cmd, &arg);
	}
	pid = fork();
	if (pid == 0)
	{
		if (fd_in >= 0)
			dup2(fd_in, STDIN_FILENO);
		if (fd_out >= 0)
			dup2(fd_out, STDOUT_FILENO);
		if (execve(path, arg, __environ) == -1)
			return (127);
	}
	else
		waitpid(pid, NULL, 0);
	return (0);
}

static void	redirect_execute(t_minishell *set, t_command *list, t_command *cmd)
{
	char		path[4096];

	if (shell_index(set, cmd, Off) >= 4)
		builtin_execute(set, list, shell_index(set, cmd, Off), cmd->name);
	else if ((search_path(set->path, cmd, path) && !access(path, F_OK)))
		set->status = command_exec(list, path, set->fd_in, set->fd_out);
	else
	{
		if (access(path, F_OK) < 0)
		{
			error(": command not found\n", path);
			set->status = 127;
			return ;
		}	
		set->status = command_exec(list, cmd->name, set->fd_in, set->fd_out);
	}
}

void	shell_redirect(t_minishell *set, t_command *cmd)
{
	t_command	*command;

	if (!valid_redirect(cmd))
		return ;
	if (count_redirects(cmd, "<<") + count_redirects(cmd, "<") > 0)
		if (!get_infile(set, cmd))
			return (close_fds(set));
	if (count_redirects(cmd, ">>") + count_redirects(cmd, ">") > 0)
		if (!get_outfile(set, cmd))
			return (close_fds(set));
	command = has_command(cmd);
	if (command)
		redirect_execute(set, cmd, command);
	close_fds(set);
	set->flag = Off;
}
