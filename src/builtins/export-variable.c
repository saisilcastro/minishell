/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:50:20 by mister-code       #+#    #+#             */
/*   Updated: 2024/01/09 16:48:50 by lde-cast         ###   ########.fr       */
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

static inline void	update_variable(t_minishell *set,
			t_variable **var, char *value)
{
	if ((*var)->value)
		free((*var)->value);
	(*var)->value = ms_strdup(value);
	(*var)->remove = Off;
	(*var)->equals = On;
	if (!ms_strncmp((*var)->name, "PATH", 4))
	{
		command_pop(&set->path);
		shell_path(set);
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
		if (var && ms_strchr(upd->name, '='))
			update_variable(set, &var, val);
		else if (!var)
		{
			if (ms_strchr(upd->name, '='))
				var = variable_push(name, val, Off, On);
			else
				var = variable_push(name, val, Off, Off);
			var_next_last(&set->var, var);
		}
		upd = upd->next;
	}
}
