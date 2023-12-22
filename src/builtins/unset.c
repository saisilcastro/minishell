/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:48:08 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/22 16:39:14 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_status	valid_name_unset(char *name, t_minishell *set)
{
	int	index;

	index = 0;
	if (ms_isalpha(name[0]) == Off && name[0] != '_')
	{
		error(": not a valid identifier", name, 2);
		set->status = 1;
		return (Off);
	}
	while (name && name[++index])
	{
		if (ms_isdigit(name[index]) == Off && ms_isalpha(name[index]) == Off
			&& name[index] != '_')
		{
			error(": not a valid identifier", name, 2);
			set->status = 1;
			return (Off);
		}
	}
	if (!ms_strncmp(name, "PATH", 4))
		if (set->path)
			command_pop(&set->path);
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
			if (!valid_name_unset(curr_cmd->name, set))
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
