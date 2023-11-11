/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:33:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/06 16:51:51 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	symbol_remover(char *command, char *buffer, int *i)
{
	int	index;

	index = 0;
	if (*command == '\"')
		return ;
	while (command[index] && command[index] != '\"')
	{
		*(buffer + *i) = command[index];
		*i += 1;
		index++;
	}
}

static void	symbol_remaider(char *command, char *buffer, int *i)
{
	int	index;

	index = 1;
	if (!command || command[1] == '\'')
		return ;
	*(buffer + *i) = command[0];
	*i += 1;
	while (command[index] && command[index] != '\'')
	{
		*(buffer + *i) = command[index];
		*i += 1;
		index++;
	}
	*(buffer + *i) = command[index];
	*i += 1;
}

void	error(t_minishell *set, char *error)
{
	ms_putstr_fd(PURPLE">minishell: " WHITE, 2);
	ms_putstr_fd(error, 2);
	write(2, "\n", 1);
	command_pop(&set->cmd);
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
		error(set, "Unclosed quotes in the string.");
	return (Off);
}

static int	catch_parsing(char *command, char *buffer, t_minishell *set)
{
	int	index;
	int	index2;

	index = -1;
	index2 = 0;
	while (command && command[++index] && !has_space(command[index]))
	{
		if (command[index] == '\'' || command[index] == '\"')
		{
			if (!quotes_is_closed(command + index, command[index], set, On))
				return (-1);
			if (command[index] == '\'')
			{
				symbol_remaider(command + index, buffer, &index2);
				if (command[index] == '\'')
					index++;
				while (command[index] && command[index] != '\'')
					index++;
			}
			else
			{
				symbol_remover(command + (index + 1), buffer, &index2);
				if (command[index] == '\"')
					index++;
				while (command[index] && command[index] != '\"')
					index++;
			}
			if (!command[index])
				break ;
		}
		else
			*(buffer + index2++) = command[index];
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
