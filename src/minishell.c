/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:25:22 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/27 14:05:16 by lde-cast         ###   ########.fr       */
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

	variable_next_last(&set->var, variable_push("test1", "Hello world!"));
	run = On;
	while (run)
	{
		command = readline(PURPLE">minishell: " WHITE);
		command_parser(&set->cmd, set->var, command);
		run = builtin_execute(set);
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
