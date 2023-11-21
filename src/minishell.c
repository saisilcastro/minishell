/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:25:22 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/21 16:37:47 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static void	change_order(t_minishell *set, char *redirect)
// {
// 	t_command	*curr;
// 	char		*temp1;
// 	char		*temp2;
// 	char		*temp3;

// 	curr = set->cmd;
// 	temp1 = ms_strdup(curr->name);
// 	temp2 = ms_strdup(curr->next->name);
// 	temp3 = ms_strdup(curr->next->next->name);
// 	free(curr->name);
// 	curr->name = ms_strdup(temp3);
// 	free(curr->next->name);
// 	curr->next->name = ms_strdup(temp1);
// 	free(curr->next->name);
// 	curr->next->next->name = ms_strdup(temp2);
// 	free(temp1);
// 	free(temp2);
// 	free(temp3);
// }

void	shell_set(t_minishell *set)
{
	if (!set)
		return ;
	set->cmd = NULL;
	set->var = NULL;
	set->path = NULL;
	set->file = NULL;
	set->status = 0;
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

	if (set->cmd->next)
	{
		i = -1;
		while (redirect[++i])
		{
			if (!ms_strncmp(set->cmd->name, redirect[i],
					ms_strlen(redirect[i])))
			{
				//change_order(set, redirect[i]);
				return (i);
			}
			else if (!ms_strncmp(set->cmd->next->name, redirect[i],
					ms_strlen(redirect[i])))
				return (i);
		}
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
