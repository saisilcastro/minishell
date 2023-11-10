/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:50:20 by mister-code       #+#    #+#             */
/*   Updated: 2023/11/10 15:32:51 by lumedeir         ###   ########.fr       */
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

static t_status	variable_check(t_variable **var, char *name)
{
	t_variable	*curr;

	curr = *var;
	while (curr)
	{
		if (!ms_strncmp(curr->name, name, ms_strlen(name)))
			return (On);
		curr = curr->next;
	}
	return (Off);
}

static t_status	valid_name(char *name)
{
	int	index;

	if (!name || !*name)
		return (Off);
	index = 0;
	if (!ms_isalpha(name[0]) && name[0] != 0x5F)
		return (Off);
	while (name[++index])
	{
		if (!ms_isalpha(name[index]) && !ms_isdigit(name[index])
			&& name[index] != 0x5F)
		{
			error("export: not a valid identifier");
			return (Off);
		}
	}
	return (On);
}

static void	new_value(t_variable **var, char *name, char *value)
{
	t_variable	*curr;

	if (!*var)
		return ;
	curr = *var;
	while (ms_strncmp(curr->name, name, ms_strlen(name)))
		curr = curr->next;
	if (curr->value)
		free (curr->value);
	if (*value)
		curr->value = ms_strdup(value);
	else
		curr->value = ms_strdup(value);
}

void	export_variable(t_variable **variable, t_command *command, t_minishell *set)
{
	t_command	*cmd;
	char		name[64];
	char		value[65535];
	char		*update;

	cmd = command;
	while (cmd)
	{
		update = cmd->name;
		update = name_get(update, name);
		update = value_get(update, value);
		if (variable_check(variable, name) && ms_strchr(cmd->name, '='))
			new_value(variable, name, value);
		else if (!variable_check(variable, name))
		{
			if (valid_name(name))
			{
				if (!ms_strlen(value) && !ms_strchr(cmd->name, '='))
					variable_next_last(variable, variable_push(name, NULL));
				else
					variable_next_last(variable, variable_push(name, value));
			}
			// else
			// 	//status=1;
		}
		cmd = cmd->next;
	}
}
