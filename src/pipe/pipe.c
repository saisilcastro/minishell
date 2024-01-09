/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:12:51 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/22 17:41:37 by mister-code      ###   ########.fr       */
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
			if (!curr->next || (!ms_strncmp(curr->next->name, "|", 1)
					&& !curr->next->flag_quotes))
			{
				set->status = 2;
				error("syntax error near unexpected token `newline'", NULL, 2);
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
		command_next_last(&set->pipe,
			command_push((*cmd)->name, (*cmd)->flag_quotes));
		command_pop_first(cmd);
		*cmd = next;
	}
}

static void	wait_for_pid(t_minishell *set)
{
	t_pid	*upd;

	upd = set->pid;
	while (upd)
	{
		waitpid(upd->id, &set->status, 0);
		if (WEXITSTATUS(set->status))
			set->status = WEXITSTATUS(set->status);
		else if (set->status == 2)
			set->status = 130;
		upd = upd->next;
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
	while (++i <= max && set->run_hdoc == On)
	{
		pipe_argument(set, &set->cmd);
		if (i == 0 && pipe_begin(set) == Off)
			error(" :command not found", set->pipe->name, 2);
		else if (i == max && pipe_end(set) == Off)
			error(" :command not found", set->pipe->name, 2);
		else if (i > 0 && i < max && pipe_between(set) == Off)
			error(" :command not found", set->pipe->name, 2);
		command_pop(&set->pipe);
	}
	wait_for_pid(set);
	if (set->fd_in_p)
		close(set->fd_in_p);
	if (set->fd_out_p)
		close(set->fd_out_p);
}
