/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:48:08 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/10 16:38:28 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset(t_minishell *set)
{
	t_variable	*var;
	t_command	*cmd;

	cmd = set->cmd;
	while (cmd)
	{
		var = set->var;
		while (var)
		{
			if (!ms_strcmp(var->name, cmd->name))
			{
				if (var->value)
					free(var->value);
				var->value = (char *)malloc(sizeof(char));
				*(var->value + 0) = '\0';
			}
			var = var->next;
		}
		cmd = cmd->next;
	}
}
