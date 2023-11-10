/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:54:25 by lde-cast          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/09 16:12:35 by lumedeir         ###   ########.fr       */
=======
/*   Updated: 2023/11/08 12:30:15 by lde-cast         ###   ########.fr       */
>>>>>>> e7bab5dce1b21612d7ec0f6979d197e57a1ff251
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_variable	*variable_clone(t_variable *variable)
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

static t_variable	*bubble_sort(t_variable *variable)
{
	t_variable	*sorted;
	t_variable	*first;
	t_variable	*second;

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
	return (sorted);
}

static void	print_sorted_command(t_variable *variable)
{
	t_variable	*sorted;
	t_variable	*upd;

	sorted = bubble_sort(variable);
	upd = sorted;
	while (upd)
	{
		if (upd->value == NULL)
			printf("declare -x %s\n", upd->name);
		else
			printf("declare -x %s=\"%s\"\n", upd->name, upd->value);
		upd = upd->next;
	}
	variable_pop(sorted);
}

void	export(t_variable **variable, t_command *command, t_minishell *set)
{
	if (command && !command->next)
		print_sorted_command(*variable);
	export_variable(variable, command->next, set);
}
