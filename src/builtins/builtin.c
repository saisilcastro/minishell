/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:46:45 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/09 16:11:42 by lumedeir         ###   ########.fr       */
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
		export(&set->var, set->cmd, set);
	if (!strncmp(set->cmd->name, "unset", 5))
		unset(&set->var, set->cmd->next);
	if (!strncmp(set->cmd->name, "env", 3))
		env();
	if (!set->cmd->next && !strncmp(set->cmd->name, "clear", 5))
		rl_clear_history();
	if (!strncmp(set->cmd->name, "exit", 4))
		return (Off);
	return (On);
}
