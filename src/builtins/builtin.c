/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:46:45 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/29 13:41:52 by mister-code      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_status	builtin_execute(t_minishell *set)
{
	t_command	*cmd;

	if (!set || !set->cmd)
		return (Off);
	if (!ms_strncmp(set->cmd->name, "echo", 4))
		echo_execute(set->cmd->next);
	if (!strncmp(set->cmd->name, "cd", 2))
		cd(set->cmd->next);
	if (!strncmp(set->cmd->name, "pwd", 3))
		pwd();
	if (!strncmp(set->cmd->name, "export", 6))
		export(&set->var, set->cmd);
	if (!strncmp(set->cmd->name, "unset", 5))
		unset(&set->var, set->cmd->next);
	if (!strncmp(set->cmd->name, "env", 3))
		env();
	if (!strncmp(set->cmd->name, "exit", 4))
		return (Off);
	return (On);
}
