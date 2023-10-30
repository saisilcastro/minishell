/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:25:22 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/27 18:24:10 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_set(t_minishell *set)
{
	if (!set)
		return ;
	set->cmd = NULL;
	set->var = NULL;
}

void	shell_loop(t_minishell *set)
{
	char		*command;
	t_status	run;
	t_variable	*curr;

	run = On;
	variable_next_last(&set->var, variable_push("test1", "Hello world!"));
	variable_next_last(&set->var, variable_push("test2", "finally works"));
	while (run)
	{
		command = readline(PURPLE">minishell: " WHITE);
		command_parser(&set->cmd, set->var, command);
		run = builtin_execute(set);
		curr = set->var;
		while (curr)
		{
			printf("%s=%s\n", curr->name, curr->value);
			curr = curr->next;
		}
		free(command);
		command_pop(&set->cmd);
	}
}

void	shell_pop(t_minishell *set)
{
	if (!set)
		return ;
	variable_pop(set->var);
	if (set->cmd)
		command_pop(&set->cmd);
}
