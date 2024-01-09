/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:50:20 by mister-code       #+#    #+#             */
/*   Updated: 2024/01/08 12:44:02 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static inline char	*name_get(t_minishell *set, char *command, char *name)
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

static inline char	*value_get(char *command, char *value)
{
	int	i;

	i = 0;
	while (*command)
		*(value + i++) = *command++;
	*(value + i) = '\0';
	return (command);
}

static inline void	new_value(t_variable **var, char *name, char *value)
{
	t_variable	*curr;
	t_variable	*temp;

	if (!*var)
		return ;
	curr = *var;
	temp = NULL;
	while (curr)
	{
		if (!ms_name_cmp(name, curr->name, ms_strlen(curr->name)))
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
	temp->equals = On;
}

static void inline	update_node(t_variable **var, char *name, char *value)
{
	if (valid_name(name, val, set))
	{
		if (!ms_strlen(val) && !ms_strchr(upd->name, '='))
			var_next_last(var, variable_push(name, NULL, Off, Off));
		else
			var_next_last(&set->var, variable_push(name, val, Off, On));
	}
}

void	export_variable(t_minishell *set, t_command *cmd)
{
	t_command	*upd;
	t_variable	*var;
	char		name[16000];
	char		val[65535];
	char		*update;

	upd = cmd->next;
	while (upd)
	{
		update = name_get(set, upd->name, name);
		update = value_get(update, val);
		var = var_search(set->var, name);
		if (name[0] && var && ms_strchr(upd->name, '=') && var->remove == Off)
			new_value(&set->var, name, val);
		else if (name[0] && (!var || var->remove == On))
		{
			
		}
		shell_path_update_exists(set, name);
		upd = upd->next;
	}
}
