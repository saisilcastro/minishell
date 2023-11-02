/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:33:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/02 12:47:03 by lumedeir         ###   ########.fr       */
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
	return (command);
}

static char	*catch_parsing(char *command, char *buffer)
{
	int	i;

	i = 0;
	while (*command && !has_space(*command))
	{
		if (*command == '\"')
			command = symbol_remover(command, buffer, &i, *command);
		if (*command == '\'')
			command = symbol_remaider(command, buffer, &i, *command);
		if (!command)
		{
			printf(PURPLE "minishell: " WHITE "command not found.\n");
			return (0);
		}
		if (!*command)
			break ;
		if (has_space(*command))
			break ;
		if (*command != '\"')
			*(buffer + i++) = *command;
		command++;
	}
	*(buffer + i) = '\0';
	printf("%s\n", buffer);
	return (command);
}

void	command_parser(t_command **list, t_variable *var, char *command)
{
	char		buffer[1024];
	int			i;

	while (*command)
	{
		while (*command && has_space(*command))
			command++;
		command = catch_parsing(command, buffer);
		command_next_last(list, command_push(buffer));
		if (!*command)
			break ;
		command++;
	}
	expansion(list, var);
}
