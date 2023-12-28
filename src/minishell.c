/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:25:22 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/28 16:37:49 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_set(t_minishell *set)
{
	if (!set)
		return ;
	set->cmd = NULL;
	set->var = NULL;
	set->path = NULL;
	set->pipe = NULL;
	set->name = NULL;
	set->pid = NULL;
	set->flag = Off;
	set->hdoc = NULL;
	set->run = On;
	set->run_hdoc = On;
	set->last_pipe = Off;
	set->status = 0;
	set->fd_in = -3;
	set->fd_out = -3;
	set->fd_in_p = -3;
	set->fd_out_p = -3;
	signal(SIGQUIT, SIG_IGN);
	environment_push(set);
	if (var_search(set->var, "HOME"))
		set->home = ms_strdup(var_search(set->var, "HOME")->value);
	shell_path(set);
	shell_function(set);
}

static int	shell_special_redirect(t_minishell *set, t_command *cmd)
{
	t_command	*curr;
	static char	*redirect[] = {"<<", ">>", "<", ">", NULL};
	int			i;

	(void)set;
	curr = cmd;
	while (curr)
	{
		i = -1;
		while (redirect[++i])
		{
			if (!ms_strncmp(curr->name, redirect[i],
					ms_strlen(redirect[i])) && !curr->flag_quotes)
			{
				if (curr->flag_quotes == Off)
					return (0);
			}
		}
		curr = curr->next;
	}
	return (-1);
}

static int	shell_special_index(t_minishell *set, t_command *cmd)
{
	t_command	*curr;

	curr = cmd;
	while (curr)
	{
		if (!ms_strncmp(curr->name, "|", 1) && !curr->flag_quotes)
		{
			if (!curr->next)
				return (printf
					("syntax error near unexpected token `newline'\n"),
					set->status = 2, -2);
			if (curr->flag_quotes == Off)
				return (1);
		}
		curr = curr->next;
	}
	return (shell_special_redirect(set, cmd));
}

int	shell_index(t_minishell *set, t_command **cmd, t_status priority)
{
	int	i;

	while (cmd && *cmd && !(*cmd)->name[0])
		command_pop_first(cmd);
	i = 0;
	if (*cmd)
		i = shell_special_index(set, *cmd);
	if (*cmd && (i == -1 || priority == Off))
	{
		if (!ms_strncmp((*cmd)->name, "echo", 4))
			return (4);
		else if (!ms_strncmp((*cmd)->name, "cd", 2))
			return (5);
		else if (!ms_strncmp((*cmd)->name, "pwd", 3))
			return (6);
		else if (!ms_strncmp((*cmd)->name, "export", 6))
			return (7);
		else if (!ms_strncmp((*cmd)->name, "unset", 5))
			return (8);
		else if (!ms_strncmp((*cmd)->name, "env", 3))
			return (9);
		else if (!ms_strncmp((*cmd)->name, "exit", 4))
			return (10);
	}
	return (i);
}

void	shell_pop(t_minishell *set)
{
	if (!set)
		return ;
	variable_pop(&set->var);
	if (set->cmd)
		command_pop(&set->cmd);
	if (set->pipe)
		command_pop(&set->pipe);
	if (set->pid)
		pid_pop(&set->pid);
	free(set->home);
	rl_clear_history();
}
