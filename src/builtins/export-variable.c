/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:50:20 by mister-code       #+#    #+#             */
/*   Updated: 2023/11/27 10:31:31 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*name_get(char *command, char *name)
{
	int	i;

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

static t_status	valid_name(char *name, t_minishell *set)
{
	int	index;

	if (!name || !*name)
		return (Off);
	index = 0;
	if (!ms_isalpha(name[0]) && name[0] != 0x5F)
	{
		set->status = -1;
		error("export: syntax erro unexpected");
		return (Off);
	}
	while (name[++index])
	{
		if (!ms_isalpha(name[index]) && !ms_isdigit(name[index])
			&& name[index] != 0x5F)
		{
			set->status = -1;
			error("export: not a valid identifier");
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

	upd = cmd;
	while (upd)
	{
		update = upd->name;
		update = name_get(update, name);
		update = value_get(update, value);
		if (variable_search(set->var, name) && ms_strchr(upd->name, '='))
			new_value(&set->var, name, value);
		else if (!variable_search(set->var, name))
		{
			if (valid_name(name, set))
			{
				if (!ms_strlen(value) && !ms_strchr(upd->name, '='))
					variable_next_last(&set->var, variable_push(name, NULL));
				else
					variable_next_last(&set->var, variable_push(name, value));
			}
		}
		upd = upd->next;
	}
}
