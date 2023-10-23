/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:55:01 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/20 19:44:10 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_parse(t_minishell *set, char *command)
{
	if (!set || !command)
		return ;
	while (*command)
	{
		printf("%c", *command);
		command++;
	}
}

void	shell_command(t_minishell *set)
{
	char	*command;

	if (!set)
		return ;
	command = readline("$");
	shell_parse(set, command);
	free(command);
}
