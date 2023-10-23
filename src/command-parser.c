/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:33:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/23 17:51:58 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <command.h>
#include <common.h>
#include <stdio.h>

static char	*symbol(t_variable *var, char **recover, int *i, char c)
{
	char		name[1024];

	//command++;
	//while (*command && *command != c)
	//{
	//	if (*command == '$')
	//	{
	//		j = 0;
	//		command++;
	//		found = variable_search(set->var, name);
	//		if (found)
	//		{
	//			*(buffer + *i) = found->value[j++];
	//			*i += 1;
	//		}
	//	}
	//	*(buffer + *i) = *command++;
	//	*i += 1;
	//}
	//if (*command != c)
	//	return (NULL);
	//command++;
	return ("\0");
}

void	command_parser(t_command **list, t_variable *var, char *command)
{
	char	buffer[1024];
	int		i;

	while (*command)
	{
		while (*command && has_space(*command))
			command++;
		i = 0;
		while (*command && !has_space(*command))
		{
			if (*command == '\'' || *command == '\"')
				command = symbol(var, (char **){buffer + i, command}, &i, *command);
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
		command_next_last(list, command_push(buffer));
		if (!*command)
			break ;
		command++;
	}
}

//"echo" "alive" "$float" "hello world $int"
