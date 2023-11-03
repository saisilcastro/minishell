/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:25:22 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/02 22:39:01 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	control_c(int signal)
{
}

static void	control_nothing(int signal)
{
}

void	shell_set(t_minishell *set)
{
	if (!set)
		return ;
	set->cmd = NULL;
	set->var = NULL;
	signal(SIGINT, control_c);
	signal(SIGQUIT, control_nothing);
	environment_push(set);
	variable_next_first(&set->var, variable_push("test", "Olá"));
	variable_next_first(&set->var, variable_push("test2", "Mundo!!"));
}

void	shell_loop(t_minishell *set)
{
	char		*command;
	t_status	run;

	run = On;
	while (run)
	{
		command = readline(PURPLE">minishell: " WHITE);
		if (!*command)
		{
			free (command);
			continue ;
		}
		add_history(command);
		command_parser(set, command);
		run = builtin_execute(set);
		if (command && *command)
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
