/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:48:08 by lumedeir          #+#    #+#             */
/*   Updated: 2023/10/29 17:55:21 by mister-code      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset(t_variable **variable, t_command *command)
{
	t_variable	*var;
	t_command	*cmd;
	t_status	found;

	cmd = command;
	while (cmd)
	{
		found = Off;
		var = *variable;
		while (var)
		{
			if (!ms_strcmp(var->name, cmd->name))
			{
				if (var->value)
					free(var->value);
				var->value = (char *)malloc(sizeof(char));
				*(var->value + 0) = '\0';
				found = On;
			}
			var = var->next;
		}
		if (!found)
			printf(PURPLE"minishell: " WHITE
					"unset:\"%s\" not found.\n", cmd->name);
		cmd = cmd->next;
	}
}
