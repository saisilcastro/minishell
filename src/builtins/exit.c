/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:09:46 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/10 17:31:37 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_fn(t_minishell *set)
{
	char	*command;

	if (!set->cmd || !set->cmd->next)
		exit((unsigned char)set->status);
	command = set->cmd->next->name;
	while (*command && (ms_isdigit(*command) || *command == '-'))
		command++;
	if (!*command)
		set->status = ms_atoi(set->cmd->next->name);
	else
		set->status = 2;
	exit(set->status);
}
