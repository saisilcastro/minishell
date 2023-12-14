/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:09:46 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/12 16:39:52 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_fn(t_minishell *set, t_command *cmd, int fd)
{
	char	*command;

	if (!cmd || !cmd->next)
		exit((unsigned char)set->status);
	command = cmd->next->name;
	if (*command && (!ms_isdigit(*command) || *command != '-'))
	{
		ms_putstr_fd("exit: numeric argument required\n", 2);
		exit(2);
	}
	if (*command && (ms_isdigit(*command) || *command == '-'))
	{	
		command++;
		while (*command && ms_isdigit(*command))
			command++;
	}
	if (!*command)
		set->status = ms_atoi(cmd->next->name);
	else
	{
		ms_putstr_fd("exit: numeric argument required\n", 2);
		exit(2);
	}
	if (cmd->next->next)
		ms_putstr_fd("exit: too many arguments\n", 2);
	exit(set->status);
}
