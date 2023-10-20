/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo-parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:39:20 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/18 17:45:12 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins/echo.h>
#include <stdio.h>

static char	*has_variable(t_echo **set, t_variable *var, char *command);
static char	*has_word(t_echo **set, char *command);

void	echo_parse(t_echo **set, t_variable *var, char *command)
{
	char	*update;

	update = command;
	while (*update)
	{
		update = has_variable(set, var, update);
		update = has_word(set, update);
		update++;
	}
}

static char	*has_word(t_echo **set, char *command)
{
	char	buffer[65535];
	int		i;

	if (*command == '$')
		return (command);
	i = 0;
	while (*command && !has_space(*command))
	{
		*(buffer + i++) = *command;
		command++;
	}
	*(buffer + i) = '\0';
	echo_next_last(set, echo_push(buffer));
	return (command);
}

static char	*has_variable(t_echo **set, t_variable *var, char *command)
{
	t_variable	*local;
	char		buffer[65535];
	int			i;

	if (*command == '$')
	{
		i = 0;
		command++;
		while (*command && !has_space(*command))
		{
			*(buffer + i++) = *command;
			command++;
		}
		*(buffer + i) = '\0';
		local = variable_search(var, buffer);
		if (local)
			echo_next_last(set, echo_push(local->value));
	}
	return (command);
}
