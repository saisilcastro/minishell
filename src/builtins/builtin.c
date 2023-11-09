/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:46:45 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/08 15:05:56 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ms_exit(t_command *cmd, short status)
{
	char	*command;

	if (!cmd)
		exit((unsigned char)status);
	command = cmd->name;
	while (*command && (ms_isdigit(*command) || *command == '-'))
		command++;
	if (!*command)
		status = ms_atoi(cmd->name);
	else
		status = 2;
	exit(status);
}

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
	if (!set->cmd->next && !strncmp(set->cmd->name, "clear", 5))
		rl_clear_history();
	if (!strncmp(set->cmd->name, "exit", 4))
		ms_exit(set->cmd->next, set->status);
	return (On);
}
