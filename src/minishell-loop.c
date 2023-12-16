/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:36:51 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/15 16:32:14 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	shell(t_minishell *set)
{
	int		i;
	int		j;

	if (!set)
		return ;
	i = shell_index(set, &set->cmd, On);
	if (i == -1 && !set->cmd)
		return ;
	if (i >= 0 && i <= 1)
		set->special[i](set, set->cmd);
	else if (i >= 4)
		set->builtin[i - 4](set, set->cmd, 1);
	else if (i == -1)
		shell_run(set);
}

void	shell_loop(t_minishell *set)
{
	char	*command;

	while (set->run)
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
		shell(set);
		if (command && *command)
			free(command);
		command_pop(&set->cmd);
	}
}
