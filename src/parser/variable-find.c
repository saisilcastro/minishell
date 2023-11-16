/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable-find.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:18:03 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/16 17:49:58 by lumedeir         ###   ########.fr       */
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
	while (list->name && list->name[++index] && index < position)
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

static int	namelen(char *str)
{
	int	index;

	index = 0;
	while (!has_space(str[index]) && (ms_isalpha(str[index])
			|| ms_isdigit(str[index]) || str[index] == 0x5F))
		index++;
	return (index - 1);
}

void	find_var(t_command *line, t_variable *var, int i,
		t_minishell *set)
{
	t_variable	*temp;
	t_variable	*curr;

	curr = var;
	temp = NULL;
	if (line->name[i] == 0x3F)
	{
		update(line, ms_itoa(set->status), 1, i - 1);
		return ;
	}
	while (curr)
	{
		if (!ms_name_cmp(line->name + i, curr->name, namelen(line->name + i)))
		{
			if (!temp)
				temp = curr;
			if (ms_strlen(curr->name) > ms_strlen(temp->name))
				temp = curr;
		}
		curr = curr->next;
	}
	if (temp)
		update(line, temp->value, ms_strlen(temp->name), i - 1);
	else
		skip(line, i);
}
