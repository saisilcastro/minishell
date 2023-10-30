/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:33:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/27 16:42:47 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*symbol(char *command, char *buffer, int *i, char c)
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

static char	*catch_parsing(char *command, char *buffer)
{
	int	i;

	i = 0;
	while (*command && !has_space(*command))
	{
		if (*command == '\"')
			command = symbol(command, buffer, &i, *command);
		if (!command)
		{
			printf(PURPLE "minishell: " WHITE "command not found.\n");
			exit(0);
		}
		if (!*command)
			break ;
		if (*command != '\"')
			*(buffer + i++) = *command;
		command++;
	}
	*(buffer + i) = '\0';
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
