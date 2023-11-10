/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:48:22 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/10 16:08:08 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	skip(t_command *list, int position)
{
	char	copy[40000];
	int		index;

	index = -1;
	while (list->name[++index] && index < (position - 1))
		copy[index] = list->name[index];
	while (list->name[position] && (list->name[position] == 0x5F
			|| ms_isalpha(list->name[position])
			|| ms_isdigit(list->name[position])))
		position++;
	while (list->name[position])
	{
		copy[index] = list->name[position++];
		index++;
	}
	copy[index] = '\0';
	free (list->name);
	list->name = ms_strdup(copy);
}

static void	update(t_command *list, char *value, int size, int position)
{
	char	copy[40000];
	int		index;
	int		index2;

	index = -1;
	while (list->name[++index] && index < position)
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
		t_minishell *set)
{
	t_variable	*temp;
	t_variable	*curr_var;

	curr_var = var;
	temp = NULL;
	// if (line->name[index] == 0x3F)
	// 	update(line, ms_atoi(set->status), ms_strlen(temp->name), index - 1);
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
		update(line, temp->value, ms_strlen(temp->name), index - 1);
	else
		skip(line, index);
}

static void	expand(t_command *list, t_variable *var, t_command **cmd,
	t_minishell *set)
{
	int	index;

	index = 0;
	while (list->name && list->name[index])
	{
		if (list->name[index] == '\'')
		{
			index++;
			while (list->name[index] && list->name[index] != '\'')
				index++;
			index++;
		}
		else if (list->name[index] == '\"')
		{
			while (list->name[++index] && list->name[index] != '"')
			{
				if (list->name[index] == '$' && (list->name[index + 1] == 0x5F
						|| ms_isalpha(list->name[index + 1])
						|| list->name[index + 1] == 0x3F))
				{
					find_var(list, var, (index + 1), cmd);
					index = 0;
				}
			}
			index++;
		}
		if (list->name && list->name[index] == '$' && (list->name[index + 1]
				== 0x5F || ms_isalpha(list->name[index + 1])
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
				expand(current, var, list, set);
			if (ms_strchr(current->name, '\'') || ms_strchr(current->name, '"'))
				remove_quotes(current, set);
			current = current->next;
		}
	}
}
