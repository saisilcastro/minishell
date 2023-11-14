/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:33:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/14 16:27:52 by lumedeir         ###   ########.fr       */
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

int	upd_index(char *command, char c)
{
	int	index;

	index = 0;
	while (command[index] != c)
		index++;
	return (index);
}

static t_status	catch_special(char *command, char *buffer, int *i, int *index)
{
	*(buffer + *i) = command[0];
	*index += 1;
	if (has_special(command[1]))
	{
		if (!has_special(command[2]) && (command[0] == '>'
				&& command[1] == '>')
			|| (command[0] == '<' && command[1] == '<'))
		{
			*index += 1;
			*i += 1;
			*(buffer + *i) = command[1];
			*i += 1;
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
	int	index2;

	index = 0;
	index2 = 0;
	if (has_special(command[index]))
	{
		if (!catch_special(command + index, buffer, &index2, &index))
			return (-1);
	}
	else
	{
		while (command && command[index] && !has_space(command[index])
			&& !has_special(command[index]))
		{
			if (command[index] == '\'' || command[index] == '\"')
			{
				if (!quotes_is_closed(command + index, command[index], set, On))
					return (-1);
				symbol_remaider(command + index, buffer, &index2, command[index]);
				index += upd_index(command + (index + 1), command[index]) + 1;
				if (!command[index])
					break ;
			}
			else
				*(buffer + index2++) = command[index];
			index++;
		}
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
