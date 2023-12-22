/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable-find.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:18:03 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/21 10:24:38 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	skip(t_command *list, int p)
{
	char	copy[40000];
	int		index;

	index = -1;
	while (list->name[++index] && index < (p - 1))
		copy[index] = list->name[index];
	if (list->name[p] && !ms_isalpha(list->name[p]) && list->name[p] != '_')
		p++;
	else
		while (list->name[p] && (ms_isalpha(list->name[p])
				|| list->name[p] == '_'))
			p++;
	while (list->name[p])
	{
		copy[index] = list->name[p++];
		index++;
	}
	copy[index] = '\0';
	free (list->name);
	list->name = ms_strdup(copy);
}

static void	update(t_command *list, char *value, int size, int position)
{
	char	copy[40000];
	int		i;
	int		index2;

	i = 0;
	while (list->name && i < position)
	{
		copy[i] = list->name[i];
		i++;
	}
	index2 = i + size + 1;
	while (value && *value)
	{
		copy[i] = *value++;
		i++;
	}
	while (list->name[index2])
	{
		copy[i] = list->name[index2];
		i++;
		index2++;
	}
	copy[i] = '\0';
	free (list->name);
	list->name = ms_strdup(copy);
}

void	find_variable(t_command *line, t_variable *var, int i,
		t_minishell *set)
{
	t_variable	*temp;
	t_variable	*curr;
	char		*status;

	curr = var;
	temp = NULL;
	if (line->name[i] == 0x3F)
	{
		status = ms_itoa(set->status);
		update(line, status, 1, i - 1);
		free(status);
		return ;
	}
	while (curr && (line->name[i + 1] == 0x5F || ms_isalpha(line->name[i + 1])))
	{
		if (!ms_name_cmp(line->name + i, curr->name, ms_strlen(curr->name)))
			if (!temp || ms_strlen(curr->name) > ms_strlen(temp->name))
				temp = curr;
		curr = curr->next;
	}
	if (temp != NULL)
		update(line, temp->value, ms_strlen(temp->name), i - 1);
	else
		skip(line, i);
}
