/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:34:05 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/02 12:18:42 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	variable_set(t_variable *set)
{
	set->name = NULL;
	set->value = NULL;
	set->next = NULL;
}

t_variable	*variable_push(char *name, char *value)
{
	t_variable	*set;

	set = (t_variable *)malloc(sizeof(t_variable));
	variable_set(set);
	set->name = ms_strdup(name);
	set->value = ms_strdup(value);
	return (set);
}

int	value_position(char *list)
{
	int	count;

	count = 0;
	if (!list)
		return (0);
	while (list[count] && list[count] != '=')
		count++;
	if (!list[count])
		return (0);
	return (count + 1);
}

t_variable	*variable_search(t_variable *list, char *name)
{
	t_variable	*update;

	update = list;
	while (update)
	{
		if (ms_strcmp(update->name, name))
			return (update);
		update = update->next;
	}
	return (NULL);
}

void	variable_pop(t_variable *head)
{
	t_variable	*next;

	while (head)
	{
		next = head->next;
		if (head->name)
			free(head->name);
		if (head->value)
			free(head->value);
		free(head);
		head = next;
	}
}
