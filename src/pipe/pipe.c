/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:12:51 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/15 18:49:57 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_status	valid_pipe(t_minishell *set, t_command *cmd)
{
	t_command	*curr;

	curr = cmd;
	while (curr)
	{
		if (!ms_strncmp(curr->name, "|", 1) && !curr->flag_quotes)
		{
			if (!curr->next || (has_special(curr->next->name[0])
					&& !curr->next->flag_quotes))
			{
				set->status = 2;
				error("syntax error near unexpected", NULL, 2);
				return (Off);
			}
		}
		curr = curr->next;
	}
	return (On);
}

static int	pipe_counter(t_command *cmd)
{
	int			count;
	t_command	*upd;
	t_status	cat;

	cat = Off;
	count = 0;
	upd = cmd;
	while (upd)
	{
		if (!ms_strncmp(upd->name, "|", 1) && !upd->flag_quotes)
			count++;
		upd = upd->next;
	}
	return (count);
}

static void	pipe_argument(t_minishell *set, t_command **cmd)
{
	t_command	*next;

	while (*cmd)
	{
		if (!ms_strncmp((*cmd)->name, "|", 1) && !(*cmd)->flag_quotes)
		{
			command_pop_first(cmd);
			break ;
		}
		next = (*cmd)->next;
		command_next_last(&set->pipe, command_push((*cmd)->name));
		command_pop_first(cmd);
		*cmd = next;
	}	
}

void	shell_pipe(t_minishell *set, t_command *cmd)
{
	int			i;
	int			max;

	if (!valid_pipe(set, cmd))
		return ;
	max = pipe_counter(cmd);
	i = -1;
	set->status = 0;
	while (++i <= max)
	{
		pipe_argument(set, &set->cmd);
		if (i == 0 && pipe_begin(set) == Off)
			error(" :command not found", set->pipe->name, 1);
		if (i == max && pipe_end(set) == Off)
			error(" :command not found", set->pipe->name, 1);
		else if (i > 0 && i < max && pipe_between(set) == Off)
			error(" :command not found", set->pipe->name, 1);
		command_pop(&set->pipe);
	}
	if (set->fd_in_p)
		close(set->fd_in_p);
	if (set->fd_out_p)
		close(set->fd_out_p);
}
