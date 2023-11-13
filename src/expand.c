/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:48:22 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/13 12:37:28 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	do_expansion(t_command *list, int *index,
	t_variable *var, t_minishell *set)
{
	*index += 1;
	while (list->name[*index] && list->name[*index] != '"')
	{
		if (list->name[*index] == '$' && (list->name[*index + 1] == 0x5F
				|| ms_isalpha(list->name[*index + 1])
				|| list->name[*index + 1] == 0x3F))
		{
			find_var(list, var, (*index + 1), set);
			*index = 0;
			break ;
		}
		*index += 1;
	}
}

static void	find_signal(t_command *list, t_variable *var, t_command **cmd,
	t_minishell *set)
{
	int	index;

	index = 0;
	while (list->name && list->name[index])
	{
		if (list->name[index] == '\'')
			index += att_index(list->name + (index + 1), '\'');
		else if (list->name[index] == '\"')
			do_expansion(list, &index, var, set);
		if (list->name[index] && list->name[index] == '$'
			&& (list->name[index + 1] == 0x5F
				|| ms_isalpha(list->name[index + 1])
				|| list->name[index + 1] == '?'))
		{
			find_var(list, var, (index + 1), set);
			index = 0;
		}
		if (list->name[index] && list->name[index]
			!= '\'' && list->name[index] != '"')
			index++;
	}
}

void	expansion(t_command **list, t_variable *var, t_minishell *set)
{
	t_command	*current;
	int			count;

	if (!*list)
		return ;
	current = (*list)->next;
	while (current)
	{
		if (!ms_strncmp((*list)->name, "export", 6)
			&& current->next && current->next->name[0] == '$')
		{
			node_delete(list, current->next->name);
			error("export: not a valid identifier");
			continue ;
		}
		else
		{
			count = value_position(current->name);
			if (current->name && ms_strchr(current->name, '$'))
				find_signal(current, var, list, set);
			if (ms_strchr(current->name, '\'') || ms_strchr(current->name, '"'))
				remove_quotes(current, set);
			current = current->next;
		}
	}
}
