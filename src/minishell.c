/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:25:22 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/22 19:25:47 by lumedeir         ###   ########.fr       */
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
	set->run = On;
	signal(SIGINT, shell_ctrl_c);
	signal(SIGQUIT, shell_ctrl_backslash);
	environment_push(set);
	variable_next_first(&set->var, variable_push("test", "Olá"));
	variable_next_first(&set->var, variable_push("test2", "Mundo!!"));
	shell_path(set);
	shell_function(set);
}

static int	shell_redirect(t_minishell *set)
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
			if (!ms_strncmp(curr->name, redirect[i],
					ms_strlen(redirect[i])))
			{
				if (!curr->next)
					printf("syntax error near unexpected token `newline'\n");
				set->status = 2;
				return (i);
			}
		}
		curr = curr->next;
	}
	return (-1);
}

int	shell_index(t_minishell *set)
{
	int	i;

	i = shell_redirect(set);
	if (i == -1)
	{
		if (!ms_strncmp(set->cmd->name, "echo", 4))
			return (4);
		else if (!ms_strncmp(set->cmd->name, "cd", 2))
			return (5);
		else if (!ms_strncmp(set->cmd->name, "pwd", 3))
			return (6);
		else if (!ms_strncmp(set->cmd->name, "export", 6))
			return (7);
		else if (!ms_strncmp(set->cmd->name, "unset", 5))
			return (8);
		else if (!ms_strncmp(set->cmd->name, "env", 3))
			return (9);
		else if (!ms_strncmp(set->cmd->name, "exit", 4))
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
