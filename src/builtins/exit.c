/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:09:46 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/23 19:24:49 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_fn(t_minishell *set, t_command *cmd)
{
	char	*command;

	if (!cmd || !cmd->next)
		exit((unsigned char)set->status);
	command = cmd->next->name;
	while (*command && (ms_isdigit(*command) || *command == '-'))
		command++;
	if (!*command)
		set->status = ms_atoi(cmd->next->name);
	else
		set->status = 2;
	if (cmd->next)
		ms_putstr_fd("exit: No such file or directory\n", 2);
	exit(set->status);
}
