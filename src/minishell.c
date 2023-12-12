/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:25:22 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/12 11:06:46 by lumedeir         ###   ########.fr       */
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
	set->file = NULL;
	set->status = 0;
	set->name = NULL;
	set->flag = Off;
	set->run = On;
	set->fd_in = -3;
	set->fd_out = -3;
	signal(SIGINT, shell_ctrl_c);
	signal(SIGQUIT, shell_ctrl_backslash);
	environment_push(set);
	variable_next_first(&set->var, variable_push("test", "Olá"));
	variable_next_first(&set->var, variable_push("test2", "Mundo!!"));
	shell_path(set);
	shell_function(set);
}

static int	shell_redirect_index(t_minishell *set)
{
	static char	*redirect[] = {"<<", ">>", "<", ">", NULL};
	int			i;
	t_command	*curr;

	curr = set->cmd;
	while (curr)
	{
		i = -1;
		while (redirect[++i])
		{
			if (!ms_strncmp(curr->name, redirect[i], ms_strlen(redirect[i])))
			{
				if (!curr->next)
				{
					printf("syntax error near unexpected token `newline'\n");
					set->status = 2;
					return (-2);
				}
				if (curr->flag_quotes == Off)
					return (0);
			}
		}
		curr = curr->next;
	}
	return (-1);
}

int	shell_index(t_minishell *set, t_command *cmd, t_status priority)
{
	int	i;

	i = shell_redirect_index(set);
	if (i == -1 || priority == Off)
	{
		if (!ms_strncmp(cmd->name, "echo", 4))
			return (4);
		else if (!ms_strncmp(cmd->name, "cd", 2))
			return (5);
		else if (!ms_strncmp(cmd->name, "pwd", 3))
			return (6);
		else if (!ms_strncmp(cmd->name, "export", 6))
			return (7);
		else if (!ms_strncmp(cmd->name, "unset", 5))
			return (8);
		else if (!ms_strncmp(cmd->name, "env", 3))
			return (9);
		else if (!ms_strncmp(cmd->name, "exit", 4))
			return (10);
	}
	return (i);
}

void	shell_pop(t_minishell *set)
{
	if (!set)
		return ;
	variable_pop(set->var);
	if (set->cmd)
		command_pop(&set->cmd);
	if (set->file)
		command_pop(&set->file);
	rl_clear_history();
}
