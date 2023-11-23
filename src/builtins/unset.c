/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:48:08 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/23 19:34:14 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset(t_minishell *set, t_command *cmd)
{
	t_variable	*var;
	t_command	*curr_cmd;

	curr_cmd = cmd;
	while (curr_cmd)
	{
		var = set->var;
		while (var)
		{
			if (!ms_strcmp(var->name, curr_cmd->name))
			{
				if (var->value)
					free(var->value);
				var->value = (char *)malloc(sizeof(char));
				*(var->value + 0) = '\0';
			}
			var = var->next;
		}
		curr_cmd = curr_cmd->next;
	}
	set->status = 0;
}
