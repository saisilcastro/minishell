/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:54:25 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/22 18:21:23 by mister-code      ###   ########.fr       */
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
		var_next_last(&set, variable_push(update->name,
				update->value, update->env));
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

static void	print_sorted_command(t_minishell *set, t_variable *variable, int fd)
{
	t_variable	*sorted;
	t_variable	*upd;

	sorted = bubble_sort(variable);
	upd = sorted;
	while (upd)
	{
		if (ms_strlen(upd->value))
		{
			ms_putstr_fd("declare -x ", fd);
			ms_putstr_fd(upd->name, fd);
			ms_putstr_fd("=\"", fd);
			ms_putstr_fd(upd->value, fd);
			ms_putstr_fd("\"\n", fd);
		}
		upd = upd->next;
	}
	variable_pop(sorted);
	set->status = 0;
}

void	export(t_minishell *set, t_command *cmd, int fd)
{
	t_command	*command;
	t_variable	*variable;

	if (set->status != 0)
		set->status = 0;
	command = cmd;
	variable = set->var;
	if (command && !command->next)
		print_sorted_command(set, variable, fd);
	export_variable(set, cmd);
}
