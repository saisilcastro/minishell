/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 21:55:01 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/04 10:08:48 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_parse(t_minishell *set, char *command)
{
	if (!set || !command)
		return ;
	while (*command)
	{
	}
	free(command);
}

void	shell_command(t_minishell *set)
{
	if (!set)
		return ;
	shell_parse(set, readline("$"));
}
