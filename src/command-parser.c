/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:33:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/02 21:25:04 by lde-cast         ###   ########.fr       */
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

//static void	error(char *error, t_minishell *set)
//{
//	ms_putstr_fd(PURPLE">minishell: " WHITE, 2);
//	ms_putstr_fd(error, 2);
//	write(2, "\n", 1);
//	command_pop(&set->cmd);
//	shell_loop(set);
//}

static char	*error(t_minishell *set, char *error)
{
	ms_putstr_fd(PURPLE">minishell: " WHITE, 2);
	ms_putstr_fd(error, 2);
	write(2, "\n", 1);
	command_pop(&set->cmd);
	return (NULL);
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
			return (error(set, "command is not valid\n"));
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
	char		*update;
	int			i;

	if (!command)
		return ;
	update = command;
	while (*update)
	{
		while (*update && has_space(*update))
			update++;
		update = catch_parsing(update, buffer, set);
		command_next_last(&set->cmd, command_push(buffer));
		if (!update || !*update)
			break ;
		update++;
	}
	expansion(&set->cmd, set->var);
}
