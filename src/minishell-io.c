/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-io.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:11:54 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/09 12:06:54 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <fcntl.h>

t_status	has_io(t_command *command)
{
	if (!command)
		return (Off);
	if (!ms_strncmp(command->name, "<", 1))
		return (On);
	if (!ms_strncmp(command->name, ">", 1))
		return (On);
	if (!ms_strncmp(command->name, "<<", 2))
		return (On);
	if (!ms_strncmp(command->name, ">>", 2))
		return (On);
	return (Off);
}

static void	shell_open(t_command *cmd, char *path, t_status *activate, int *fd)
{
	t_command	*io;

	io = cmd->next;
	if (!ms_strncmp(io->name, ">", 1))
	{
		if (!*activate)
			*fd = open(path, O_WRONLY | O_CREAT);
		else
			*fd = open(path, O_WRONLY);
	}
	*activate = On;
}

t_status	shell_io(t_minishell *set)
{
	t_command	*cmd;
	t_status	activate;
	int			fd;

	if (!set || !set->cmd || !has_io(set->cmd->next))
		return (Off);
	fd = -1;
	activate = Off;
	cmd = set->cmd->next->next;
	while (cmd)
	{
		shell_open(set->cmd, cmd->name, &activate, &fd);
		if (cmd->next)
			close(fd);
		cmd = cmd->next;
	}
	close(fd);
	return (On);
}
