/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:48:22 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/06 16:33:08 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

static void	update_quotes(t_command *list, t_minishell *set)
{
	char	copy[40000];
	int		index;
	int		index2;

	index = -1;
	while (list->name[++index] && list->name[index] != '\'')
		copy[index] = list->name[index];
	if (!quotes_is_closed(list->name + index, list->name[index], set, Off))
		return ;
	index2 = index;
	while (list->name[++index2] && list->name[index2] != '\'')
	{
		copy[index] = list->name[index2];
		index++;
	}
	while (list->name[++index2] && list->name[index2] != '\0')
	{
		copy[index] = list->name[index2];
		index++;
	}
	copy[index] = '\0';
	free (list->name);
	list->name = ms_strdup(copy);
	if (ms_strchr(list->name, '\''))
		update_quotes(list, set);
}

static void	update(t_command *list, char *value, int size)
{
	char	copy[40000];
	int		index;
	int		index2;

	index = -1;
	while (list->name[++index] && list->name[index] != '$')
		copy[index] = list->name[index];
	index2 = index + size + 1;
	while (value && *value)
	{
		copy[index] = *value++;
		index++;
	}
	while (list->name[index2])
	{
		copy[index] = list->name[index2];
		index++;
		index2++;
	}
	copy[index] = '\0';
	free (list->name);
	list->name = ms_strdup(copy);
}

static void	find_var(t_command *line, t_variable *var, int index,
		t_command **list)
{
	t_variable	*temp;
	t_variable	*curr_var;

	curr_var = var;
	temp = NULL;
	while (curr_var)
	{
		if (!ms_name_cmp(line->name + index,
				curr_var->name, ms_strlen(curr_var->name)))
		{
			if (!temp)
				temp = curr_var;
			if (ms_strlen(curr_var->name) > ms_strlen(temp->name))
				temp = curr_var;
		}
		curr_var = curr_var->next;
	}
	if (temp)
		update(line, temp->value, ms_strlen(temp->name));
	else if (line->name[0] == '$')
		node_delete(list, line->name);
}

static void	expand(t_command *list, t_variable *var, t_command **cmd,
	t_minishell *set)
{
	int	index;

	index = 0;
	while (list->name && list->name[index])
	{
		if (list->name[index] == '\''
			&& quotes_is_closed(list->name + index,
				list->name[index], set, Off))
		{
			index++;
			while (list->name[index] && list->name[index] != '\'')
				index++;
			index++;
		}
		if (list->name && !list->name[index])
			break ;
		if (list->name && list->name[index] == '$')
			find_var(list, var, (index + 1), cmd);
		if (list->name[index] != '\'')
			index++;
	}
	if (ms_strchr(list->name, '\''))
		update_quotes(list, set);
}

void	expansion(t_command **list, t_variable *var, t_minishell *set)
{
	t_command	*current;
	t_status	permission;
	int			count;

	if (!*list)
		return ;
	current = (*list)->next;
	permission = On;
	while (current)
	{
		if (!ms_strncmp((*list)->name, "export", 6)
			&& current->next && current->next->name[0] == '$')
		{
			node_delete(list, current->next->name);
			continue ;
		}
		else
		{
			count = value_position(current->name);
			if (current->name && ms_strchr(current->name, '$'))
				expand(current, var, list, set);
			current = current->next;
		}
	}
}
