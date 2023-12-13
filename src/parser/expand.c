/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:48:22 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/13 10:56:34 by lumedeir         ###   ########.fr       */
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
			find_variable(list, var, (*index + 1), set);
			*index = 0;
			break ;
		}
		*index += 1;
	}
}

static void	find_signal(t_command *list, t_variable *var, t_command **cmd,
	t_minishell *set)
{
	int	i;

	i = 0;
	while (list->name && list->name[i])
	{
		if (list->name[i] == '\'' && list->name[i + 1])
			i += upd_index(list->name + (i + 1), '\'');
		else if (list->name[i] == '\"' && list->name[i + 1])
			do_expansion(list, &i, var, set);
		if (list->name[i] && list->name[i + 1] && list->name[i] == '$'
			&& (ms_isalpha(list->name[i + 1])
				|| list->name[i + 1] == '_' || list->name[i + 1] == '?'))
		{
			find_variable(list, var, (i + 1), set);
			i = 0;
			continue ;
		}
		if ((list->name[i] == '"' || list->name[i] == '\'')
			&& !list->name[i + 1])
			i++;
		else if (list->name[i] && list->name[i]
			!= '\'' && list->name[i] != '"')
			i++;
	}
}

void	expansion(t_command **list, t_variable *var, t_minishell *set)
{
	t_command	*current;

	if (!*list)
		return ;
	current = *list;
	while (current)
	{
		if (current->name && ms_strchr(current->name, '$'))
			find_signal(current, var, list, set);
		if (ms_strchr(current->name, '\'') || ms_strchr(current->name, '"'))
		{
			current->flag_quotes = On;
			remove_quotes(current, set);
		}
		current = current->next;
	}
}
