/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:48:08 by lumedeir          #+#    #+#             */
/*   Updated: 2023/10/27 20:38:42 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset(t_variable **variable, t_command *command)
{
	t_variable	*var;
	t_command	*cmd;

	var = *variable;
	while (var)
	{
		cmd = command;
		while (cmd)
		{
			if (!strcmp(var->name, cmd->name))
			{
				free(var->value);
				var->value = (char *)malloc(sizeof(char));
				*(var->value + 0) = '\0';
			}
			else
				printf(PURPLE"minishell: " WHITE
					"unset:\"%s\" not found.\n", cmd->name);
			cmd = cmd->next;
		}
		var = var->next;
	}
}
