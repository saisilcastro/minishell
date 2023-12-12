/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:48:08 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/12 15:55:38 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_status	check_name(t_minishell *set, t_command *curr_cmd)
{
	if (curr_cmd->name[0] && !ms_isalpha(curr_cmd->name[0])
		&& curr_cmd->name[0] != '_')
	{
		set->status = 1;
		error(" not a valid identifier", curr_cmd->name);
		return (Off);
	}
	return (On);
}

void	unset(t_minishell *set, t_command *cmd, int fd)
{
	t_variable	*var;
	t_command	*curr_cmd;

	(void)fd;
	if (!cmd->next || !*cmd->name)
		return ;
	curr_cmd = cmd->next;
	while (curr_cmd)
	{
		var = set->var;
		while (var)
		{
			if (!check_name(set, curr_cmd))
				break ;
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
}
