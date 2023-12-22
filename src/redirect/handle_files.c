/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:38:59 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/22 18:41:34 by mister-code      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_status	close_fds(t_minishell *set)
{
	if (set->fd_in >= 0 && close(set->fd_in) == -1)
		return (Off);
	if (set->fd_out >= 0 && close(set->fd_out) == -1)
		return (Off);
	set->fd_out = -3;
	set->fd_in = -3;
	return (Off);
}

void	fd_reset(t_minishell *set)
{
	set->fd_in = -3;
	set->fd_out = -3;
	set->fd_in_p = -3;
	set->fd_out_p = -3;
	set->run_hdoc = On;
}

t_status	open_fds(t_minishell *set, char *redirect, char *name)
{
	if (!ms_strncmp(redirect, "<", 1))
	{
		set->fd_in = open(name, O_RDONLY, 0777);
		if (set->fd_in < 0)
		{
			set->name = name;
			set->status = 1;
			return (Off);
		}
		return (On);
	}
	if (!ms_strncmp(redirect, ">>", 2))
		set->fd_out = open(name, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else if (!ms_strncmp(redirect, ">", 1))
		set->fd_out = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (set->fd_out < 0)
	{
		error(": No such file or directory", name, 2);
		set->status = 1;
		return (Off);
	}
	return (On);
}

t_status	get_infile(t_minishell *set, t_command *cmd)
{
	if (set->fd_in >= 0)
		close(set->fd_in);
	if (!ms_strncmp(cmd->name, "<<", 2))
		heredoc(set, cmd->next->name);
	else if (!open_fds(set, "<", cmd->next->name))
	{
		error(": No such file or directory", set->name, 2);
		close_fds(set);
		return (Off);
	}
	return (On);
}
