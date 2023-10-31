/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:25:22 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/31 11:15:23 by lumedeir         ###   ########.fr       */
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

	environment_push(set);
	run = On;
	variable_next_first(&set->var, variable_push("test", "80"));
	variable_next_first(&set->var, variable_push("test2", "90"));
	while (run)
	{
		command = readline(PURPLE">minishell: " WHITE);
		add_history(command);
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
	rl_clear_history();
}
