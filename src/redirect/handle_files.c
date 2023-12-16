/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:38:59 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/15 18:48:43 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_fds(t_minishell *set)
{
	if (set->fd_in >= 0 && close(set->fd_in) == -1)
		return ;
	if (set->fd_out >= 0 && close(set->fd_out) == -1)
		return ;
	set->fd_out = -3;
	set->fd_in = -3;
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
		set->fd_out = open(name, O_WRONLY | O_APPEND | O_CREAT, 00700);
	else if (!ms_strncmp(redirect, ">", 1))
		set->fd_out = open(name, O_WRONLY | O_CREAT | O_TRUNC, 00700);
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
	t_command	*curr;
	int			count_in;

	curr = cmd;
	count_in = count_redirects(cmd, "<<") + count_redirects(cmd, "<");
	while (curr && count_in)
	{
		if (!curr->flag_quotes && (!ms_strncmp(curr->name, "<<", 2)
				|| !ms_strncmp(curr->name, "<", 1)))
		{
			if (set->fd_in >= 0)
				close_fds(set);
			if (!ms_strncmp(curr->name, "<<", 2))
				heredoc(set, cmd, curr->next->name);
			else if (!open_fds(set, "<", curr->next->name))
				set->flag = On;
			count_in--;
		}
		curr = curr->next;
	}
	if (set->flag)
		return (error(": No such file or directory", set->name, 2), Off);
	return (On);
}

t_status	get_outfile(t_minishell *set, t_command *cmd)
{
	t_command	*curr;
	int			count_out;

	curr = cmd;
	count_out = count_redirects(cmd, ">>") + count_redirects(cmd, ">");
	while (curr && count_out)
	{
		if (!curr->flag_quotes && (!ms_strncmp(curr->name, ">>", 2)
				|| !ms_strncmp(curr->name, ">", 1)))
		{
			if (set->fd_out >= 0)
			{
				close(set->fd_out);
				set->fd_out = -3;
			}
			open_fds(set, curr->name, curr->next->name);
			curr = curr->next;
			count_out--;
		}
		curr = curr->next;
	}
	return (On);
}
