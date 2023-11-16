/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:33:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/16 17:36:49 by lumedeir         ###   ########.fr       */
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
		if (!has_special(command[2]) && (command[0] == '>'
				&& command[1] == '>')
			|| (command[0] == '<' && command[1] == '<'))
		{
			*index += 1;
			i++;
			*(buffer + i) = command[1];
			i++;
		}
		else
		{
			error("error: syntax error unexpected");
			return (Off);
		}
	}
	return (On);
}

static int	catch_parsing(char *command, char *buffer, t_minishell *set)
{
	int	index;

	index = 0;
	if (has_special(command[index]))
	{
		if (!catch_special(command + index, buffer, &index))
			return (-1);
	}
	else
		index = handle_quotes(command, buffer, set);
	return (index);
}

void	symbol_remaider(char *command, char *buffer, int *i, char c)
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

int	upd_index(char *command, char c)
{
	int	index;

	index = 0;
	while (command[index] != c)
		index++;
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
		{
			set->status = -1;
			return (Off);
		}
		command_next_last(&set->cmd, command_push(buffer));
		index += update;
	}
	expansion(&set->cmd, set->var, set);
	return (On);
}
