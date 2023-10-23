/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:25:22 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/23 14:55:33 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_set(t_minishell *set)
{
	if (!set)
		return ;
	set->cmd = NULL;
}

void	shell_loop(t_minishell *set)
{
	char	*command;
	t_command	*upd;

	command = readline(">");
	command_parser(&set->cmd, command);
	upd = set->cmd;
	while (upd)
	{
		printf("%s\n", upd->name);
		upd = upd->next;
	}
	free(command);
}

void	shell_pop(t_minishell *set)
{
	if (!set)
		return ;
}
