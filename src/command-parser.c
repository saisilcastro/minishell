/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:33:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/13 11:37:45 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	symbol_remaider(char *command, char *buffer, int *i, char c)
{
	int	index;

	index = 1;
	if (!command || command[1] == c)
		return ;
	*(buffer + *i) = command[0];
	*i += 1;
	while (command[index] && command[index] != c)
	{
		*(buffer + *i) = command[index];
		*i += 1;
		index++;
	}
	*(buffer + *i) = command[index];
	*i += 1;
}

t_status	quotes_is_closed(char *command, char c,
	t_minishell *set, t_status msg)
{
	int	index;

	index = 0;
	while (command && command[++index])
	{
		if (command[index] == c)
			return (On);
	}
	if (msg == On)
		error_and_clear(set, "Unclosed quotes in the string.");
	return (Off);
}

int	att_index(char *command, char c)
{
	int	index;

	index = 0;
	while (command[index] != c)
		index++;
	return (index);
}

static int	catch_parsing(char *command, char *buffer, t_minishell *set)
{
	int	index;
	int	index2;

	index = 0;
	index2 = 0;
	while (command && command[index] && !has_space(command[index]))
	{
		if (command[index] == '\'' || command[index] == '\"')
		{
			if (!quotes_is_closed(command + index, command[index], set, On))
				return (-1);
			symbol_remaider(command + index, buffer, &index2, command[index]);
			if (command[index] == '\'')
				index += att_index(command + (index + 1), '\'') + 1;
			else
				index += att_index(command + (index + 1), '"') + 1;
			if (!command[index])
				break ;
		}
		else
			*(buffer + index2++) = command[index];
		index++;
	}
	*(buffer + index2) = '\0';
	return (index);
}

t_status	command_parser(t_minishell *set, char *command)
{
	char		buffer[4050];
	int			update;
	int			index;

	if (!command)
		return (Off);
	index = 0;
	while (command[index])
	{
		while (command[index] && has_space(command[index]))
			index++;
		update = catch_parsing(command + index, buffer, set);
		if (update == -1)
			return (Off);
		command_next_last(&set->cmd, command_push(buffer));
		index += update;
	}
	expansion(&set->cmd, set->var, set);
	return (On);
}
