/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:36:51 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/09 12:05:33 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_status	shell_execute(t_minishell *set)
{
	t_status	execute;

	if (!set)
		return (Off);
	execute = shell_io(set);
	execute = builtin_execute(set);
	return (execute);
}

void	shell_loop(t_minishell *set)
{
	char		*command;
	t_status	run;

	run = On;
	while (run)
	{
		set->status = 0;
		command = readline(PURPLE">minishell: " WHITE);
		if (!*command)
		{
			free (command);
			continue ;
		}
		add_history(command);
		if (!command_parser(set, command))
		{
			free (command);
			continue ;
		}
		run = shell_execute(set);
		if (command && *command)
			free(command);
		command_pop(&set->cmd);
	}
}
