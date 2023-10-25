/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:25:22 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/25 15:55:51 by lde-cast         ###   ########.fr       */
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
	t_command	*upd;

	command = readline(PURPLE">minishell: " WHITE);
	variable_next_last(&set->var, variable_push("test1", "Hello world!"));
	variable_next_last(&set->var, variable_push("test2", "finally works"));
	command_parser(&set->cmd, set->var, command);
	upd = set->cmd;
	while (upd)
	{
		printf("%s\n", upd->name);
		upd = upd->next;
	}
	free(command);
}

void	shell_pop(t_minishell *set)
{
	if (!set)
		return ;
	variable_pop(set->var);
	command_pop(set->cmd);
}
