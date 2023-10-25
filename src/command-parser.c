/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:33:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/25 16:25:19 by lumedeir         ###   ########.fr       */
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
		if (*command == '\'' || *command == '\"')
			command = symbol(command, buffer, &i, *command);
		if (!command)
		{
			printf(PURPLE "minishell: " WHITE "command not found.\n");
			exit(0);
		}
		if (!*command)
			break ;
		*(buffer + i++) = *command++;
	}
	*(buffer + i) = '\0';
	return (command);
}

static void	call_bulting(char *bulting, t_command *list, t_variable *var)
{
	// if (ms_strcmp("echo", bulting))
	// 	echo();
	// if (ms_strcmp("cd", bulting))
	// 	cd();
	if (ms_strcmp("pwd", bulting))
		pwd();
	// else if (ms_strcmp("export", bulting))
	// 	export(&list, var);
	// else if (ms_strcmp("unset", bulting))
	// 	unset(var, line);
	else if (ms_strcmp("env", bulting))
		env();
	// if (ms_strcmp("exit", bulting))
	// 	exit();
}

void	command_parser(t_command **list, t_variable *var, char *command)
{
	char	buffer[1024];
	int		i;

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
	call_bulting((*list)->name, (*list)->next, var);
}
