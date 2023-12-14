/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:12:51 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/14 19:34:52 by lde-cast         ###   ########.fr       */
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
				error("syntax error near unexpected", NULL);
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
	i = 0;
	while (i <= max)
	{
		pipe_argument(set, &set->cmd);
		if (i == 0)
			pipe_begin(set);
		else if (i == max)
			pipe_end(set);
		else
			pipe_between(set);
		command_pop(&set->pipe);
		i++;
	}
}
