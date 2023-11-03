/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:48:22 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/02 21:08:13 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

static void	update_quotes(t_command *list)
{
	char	copy[40000];
	int		index;
	int		index2;

	index = -1;
	while (list->name[++index] && list->name[index] != '\'')
		copy[index] = list->name[index];
	index2 = index;
	while (list->name[++index2] && list->name[index2] != '\'')
	{
		copy[index] = list->name[index2];
		index++;
	}
	copy[index] = '\0';
	free (list->name);
	list->name = ms_strdup(copy);
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

static void	expand(t_command *list, t_variable *var, t_command **cmd)
{
	int	index;

	index = 0;
	while (list->name && list->name[index])
	{
		while (list->name[index] && list->name[index] != '$')
			index++;
		if (list->name && !list->name[index])
			break ;
		if (list->name && list->name[index] == '$')
			find_var(list, var, (index + 1), cmd);
		index++;
	}
}

void	expansion(t_command **list, t_variable *var)
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
			continue ;
		}
		else
		{
			count = value_position(current->name);
			if (current->name && current->name[count] == '\''
				&& current->name[ms_strlen(current->name)] == '\'')
				update_quotes(current);
			else if (current->name && ms_strchr(current->name, '$'))
				expand(current, var, list);
			current = current->next;
		}
	}
}
