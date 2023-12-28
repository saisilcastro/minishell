/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:34:05 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/28 16:39:09 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	variable_set(t_variable *set)
{
	set->name = NULL;
	set->value = NULL;
	set->next = NULL;
}

t_variable	*variable_push(char *name, char *value, t_status env)
{
	t_variable	*set;

	set = (t_variable *)malloc(sizeof(t_variable));
	variable_set(set);
	set->name = ms_strdup(name);
	set->value = ms_strdup(value);
	set->env = env;
	return (set);
}

t_variable	*var_search(t_variable *list, char *name)
{
	t_variable	*update;

	update = list;
	while (update)
	{
		if (!ms_strncmp(update->name, name, ms_strlen(name)))
			return (update);
		update = update->next;
	}
	return (NULL);
}

void	variable_pop(t_variable **head)
{
	t_variable	*next;

	while (*head)
	{
		next = (*head)->next;
		if ((*head)->name)
			free((*head)->name);
		if ((*head)->value)
			free((*head)->value);
		free(*head);
		*head = next;
	}
	*head = NULL;
}
