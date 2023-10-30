/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export-variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:50:20 by mister-code       #+#    #+#             */
/*   Updated: 2023/10/29 17:26:39 by mister-code      ###   ########.fr       */
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

void	export_variable(t_variable **variable, t_command *command)
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
		variable_next_last(variable, variable_push(name, value));
		cmd = cmd->next;
	}
}