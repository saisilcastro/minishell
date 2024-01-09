/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_push.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:05:32 by mister-code       #+#    #+#             */
/*   Updated: 2024/01/08 12:30:14 by lde-cast         ###   ########.fr       */
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

void	environment_push(t_minishell *set)
{
	extern char	**__environ;
	char		*command;
	char		name[64];
	char		value[65535];
	int			i;

	i = -1;
	while (*(__environ + ++i))
	{
		command = *(__environ + i);
		command = name_get(command, name);
		command = value_get(command, value);
		var_next_last(&set->var, variable_push(name, value, Off, On));
	}
}
