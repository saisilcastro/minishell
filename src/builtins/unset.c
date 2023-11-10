/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:48:08 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/10 12:10:33 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset(t_variable **variable, t_command *command)
{
	t_variable	*var;
	t_command	*cmd;

	cmd = command;
	while (cmd)
	{
		var = *variable;
		while (var)
		{
			if (!ms_strcmp(var->name, cmd->name))
			{
				variable_delete(variable, cmd->name);
				break ;
			}
			var = var->next;
		}
		cmd = cmd->next;
	}
}
