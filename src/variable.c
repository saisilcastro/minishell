/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:34:05 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/18 12:59:59 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <variable.h>
#include <stdlib.h>

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
	set->name = name;
	set->value = value;
	return (set);
}

void	variable_pop(t_variable *head)
{
	t_variable	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}
