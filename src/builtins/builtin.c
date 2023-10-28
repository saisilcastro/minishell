/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:46:45 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/27 20:28:55 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_status	builtin_execute(t_minishell *set)
{
	t_command	*cmd;

	if (!set || !set->cmd)
		return (Off);
	if (!ms_strncmp(set->cmd->name, "echo", ms_strlen(set->cmd->name)))
		echo_execute(set->cmd->next);
	if (!strncmp(set->cmd->name, "cd", ms_strlen(set->cmd->name)))
		cd(set->cmd->next);
	if (!strncmp(set->cmd->name, "pwd", ms_strlen(set->cmd->name)))
		pwd();
	if (!strncmp(set->cmd->name, "export", ms_strlen(set->cmd->name)))
		return (Off);
	if (!strncmp(set->cmd->name, "unset", ms_strlen(set->cmd->name)))
		unset(&set->var, set->cmd->next);
	if (!strncmp(set->cmd->name, "env", ms_strlen("env")))
		env();
	if (!strncmp(set->cmd->name, "exit", ms_strlen("exit")))
		return (Off);
	return (On);
}
