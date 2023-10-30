/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:54:25 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/29 17:39:20 by mister-code      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_variable *variable_clone(t_variable *variable)
{
	t_variable	*set;
	t_variable	*update;

	set = NULL;
	update = variable;
	while (update)
	{
		variable_next_last(&set, variable_push(update->name, update->value));
		update = update->next;
	}
	return (set);
}

void	variable_swap(t_variable **first, t_variable **second)
{
	t_variable	upd;

	if (!*first || !*second)
		return ;
	upd.name = (*first)->name;
	upd.value = (*first)->value;
	(*first)->name = (*second)->name;
	(*first)->value = (*second)->value;
	(*second)->name = upd.name;
	(*second)->value = upd.value;
}

static void	print_sorted_command(t_variable *variable)
{
	t_variable	*sorted;
	t_variable	*first;
	t_variable	*second;
	t_variable	*upd;
	
	sorted = variable_clone(variable);
	first = sorted;
	while (first)
	{
		second = first->next;
		while (second)
		{
			if (ms_strcmp(first->name, second->name) > 0)
				variable_swap(&first, &second);
			second = second->next;
		}
		first = first->next;
	}
	upd = sorted;
	while (upd)
	{
		if (ms_strlen(upd->value))
			printf("declare -x %s=\"%s\"\n", upd->name, upd->value);
		upd = upd->next;
	}
	variable_pop(sorted);
}

void	export(t_variable **variable, t_command *command)
{
	if (command && !command->next)
		print_sorted_command(*variable);
	export_variable(variable, command->next);
}
