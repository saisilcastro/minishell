/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:50:20 by mister-code       #+#    #+#             */
/*   Updated: 2023/12/15 10:43:47 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*name_get(t_minishell *set, char *command, char *name)
{
	int	i;

	if (*command && *command == '=')
	{
		set->status = 1;
		error(": not a valid identifier", command, 2);
		*(name + 0) = '\0';
		return (command);
	}
	i = 0;
	while (*command && *command != '=')
		*(name + i++) = *command++;
	*(name + i) = '\0';
	if (*command == '=')
		command++;
	return (command);
}

static char	*value_get(char *command, char *value)
{
	int	i;

	i = 0;
	while (*command)
		*(value + i++) = *command++;
	*(value + i) = '\0';
	return (command);
}

t_status	valid_name(char *name, t_minishell *set)
{
	int	index;

	index = -1;
	if (!ms_isalpha(name[0]) && name[0] != '_'
		&& !ms_isdigit(name[0]) && name[0] != '/' && name[0] != '=')
	{
		if (name[0] == '-')
			error(": invalid option", name, 2);
		else
			error(": syntax erro unexpected", name, 2);
		set->status = 2;
		return (Off);
	}
	while (name && name[++index])
	{
		if (ms_isdigit(name[index]) || name[index] == '/' || name[index] == '='
			|| (!ms_isalpha(name[index]) && name[index] != '_'))
		{
			error(": not a valid identifier", name, 2);
			set->status = 1;
			return (Off);
		}
	}
	return (On);
}

static void	new_value(t_variable **var, char *name, char *value)
{
	t_variable	*curr;
	t_variable	*temp;

	if (!*var)
		return ;
	curr = *var;
	temp = NULL;
	while (curr)
	{
		if (!ms_name_cmp(name,
				curr->name, ms_strlen(curr->name)))
		{
			if (!temp)
				temp = curr;
			if (ms_strlen(curr->name) > ms_strlen(temp->name))
				temp = curr;
		}
		curr = curr->next;
	}
	if (temp->value)
		free (temp->value);
	if (*value)
		temp->value = ms_strdup(value);
	else
		temp->value = ms_strdup(value);
}

void	export_variable(t_minishell *set, t_command *cmd)
{
	t_command	*upd;
	char		name[64];
	char		value[65535];
	char		*update;

	upd = cmd->next;
	while (upd)
	{
		update = upd->name;
		update = name_get(set, update, name);
		update = value_get(update, value);
		if (name[0] && var_search(set->var, name) && ms_strchr(upd->name, '='))
			new_value(&set->var, name, value);
		else if (name[0] && !var_search(set->var, name))
		{
			if (valid_name(name, set))
			{
				if (!ms_strlen(value) && !ms_strchr(upd->name, '='))
					var_next_last(&set->var, variable_push(name, NULL, Off));
				else
					var_next_last(&set->var, variable_push(name, value, Off));
			}
		}
		upd = upd->next;
	}
}
