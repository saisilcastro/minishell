/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:33:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/02 18:03:29 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*symbol_remover(char *command, char *buffer, int *i, char c)
{
	command++;
	while (*command && *command != c)
	{
		*(buffer + *i) = *command++;
		*i += 1;
	}
	if (*command != c)
		return (NULL);
	return (command);
}

static char	*symbol_remaider(char *command, char *buffer, int *i, char c)
{
	*(buffer + *i) = *command++;
	*i += 1;
	while (*command && *command != c)
	{
		*(buffer + *i) = *command++;
		*i += 1;
	}
	if (*command == c)
	{
		*(buffer + *i) = *command++;
		*i += 1;
	}
	if (*command != c)
		return (NULL);
	return (command);
}

static char	*catch_parsing(char *command, char *buffer, t_minishell *set)
{
	int	i;

	i = 0;
	while (*command && !has_space(*command))
	{
		if (*command == '\"')
			command = symbol_remover(command, buffer, &i, *command);
		else if (command && *command == '\'')
			command = symbol_remaider(command, buffer, &i, *command);
		if (!command)
			error("Error: Unclosed quotes in the string.", &command, set);
		if (!*command)
			break ;
		if (has_space(*command))
			break ;
		if (*command != '\"')
			*(buffer + i++) = *command;
		command++;
	}
	*(buffer + i) = '\0';
	return (command);
}

void	command_parser(t_minishell *set, char *command)
{
	char		buffer[1024];
	int			i;

	if (!command)
		return ;
	while (*command)
	{
		while (*command && has_space(*command))
			command++;
		command = catch_parsing(command, buffer, set);
		command_next_last(&set->cmd, command_push(buffer));
		if (!command || !*command)
			break ;
		command++;
	}
	expansion(&set->cmd, set->var);
}
