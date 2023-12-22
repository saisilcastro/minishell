/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:33:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/22 18:54:00 by mister-code      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_status	catch_special(char *command, char *buffer, int *index)
{
	int	i;

	i = 0;
	*(buffer + i) = command[0];
	*index += 1;
	if (has_special(command[1]))
	{
		if (!has_special(command[2]) && ((command[0] == '>'
					&& command[1] == '>')
				|| (command[0] == '<' && command[1] == '<')))
		{
			*index += 1;
			i++;
			*(buffer + i) = command[1];
		}
		else
		{
			error("error: syntax error unexpected", NULL, 2);
			return (Off);
		}
	}
	i++;
	*(buffer + i) = '\0';
	return (On);
}

static int	catch_parsing(char *command, char *buffer, t_minishell *set)
{
	int	index;

	index = 0;
	if (has_special(command[index]))
	{
		if (catch_special(command + index, buffer, &index) == Off)
			return (-1);
	}
	else
		index = handle_quotes(command, buffer, set);
	return (index);
}

static t_status	command_error(t_minishell *set, char *command)
{
	if (!command || command[0] == '|')
	{
		if (command[0] == '|')
		{
			set->status = 2;
			error("error: syntax error unexpected", NULL, 2);
		}
		return (Off);
	}
	return (On);
}

t_status	command_parser(t_minishell *set, char *command)
{
	char		buffer[4050];
	int			update;
	int			index;

	if (command_error(set, command) == Off)
		return (Off);
	index = 0;
	while (command[index])
	{
		while (command[index] && has_space(command[index]))
			index++;
		update = catch_parsing(command + index, buffer, set);
		if (update == -1)
		{
			set->status = 2;
			command_pop(&set->cmd);
			return (Off);
		}
		if (*buffer)
			command_next_last(&set->cmd, command_push(buffer, Off));
		index += update;
	}
	expansion(&set->cmd, set->var, set);
	return (On);
}
