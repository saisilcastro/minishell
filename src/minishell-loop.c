/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:36:51 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/17 13:47:09 by lumedeir         ###   ########.fr       */
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
			command_pop(&set->cmd);
			free (command);
			continue ;
		}
		shell_execute(set);
		if (command && *command)
			free(command);
		command_pop(&set->cmd);
	}
}
