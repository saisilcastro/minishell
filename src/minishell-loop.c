/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:36:51 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/20 13:22:07 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	shell_execute(t_minishell *set)
{
	int	i;
	int	j;

	if (!set)
		return ;
	i = shell_index(set);
	if (i >= 0 && i <= 3)
		set->redirect[i](set);
	else if (i >= 4)
		set->builtin[i - 4](set);
}

void	shell_loop(t_minishell *set)
{
	char		*command;
	t_status	run;

	run = On;
	while (run)
	{
		command = readline(PURPLE">minishell: " WHITE);
		if (!*command)
		{
			free (command);
			continue ;
		}
		add_history(command);
		if (!command_parser(set, command))
		{
			free (command);
			continue ;
		}
		shell_execute(set);
		if (command && *command)
			free(command);
		command_pop(&set->cmd);
	}
}
