/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:48:08 by lumedeir          #+#    #+#             */
/*   Updated: 2024/01/08 11:31:03 by lde-cast         ###   ########.fr       */
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
		command_pop(&set->path);
	return (On);
}

static inline void	remove_apply(t_variable **var)
{
	if ((*var)->value)
		free((*var)->value);
	(*var)->value = (char *)malloc(sizeof(char));
	*((*var)->value + 0) = '\0';
	(*var)->remove = On;
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
				remove_apply(&var);
			}
			var = var->next;
		}
		curr_cmd = curr_cmd->next;
	}
}
