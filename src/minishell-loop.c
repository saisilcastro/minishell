/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:36:51 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/28 15:59:47 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_minishell	*shell_get(void)
{
	static t_minishell	shell;

	return (&shell);
}

static void	shell(t_minishell *set)
{
	int		i;

	if (!set)
		return ;
	i = shell_index(set, &set->cmd, On);
	if (!set->cmd)
	{
		set->status = 0;
		return ;
	}
	if (i == -1 && !set->cmd)
		return ;
	if (i >= 0 && i <= 1)
		set->special[i](set, set->cmd);
	else if (i >= 4)
		set->builtin[i - 4](set, set->cmd, 1);
	else if (i == -1)
		shell_run(set);
}

static t_status	verify(char **command)
{
	if (*command == NULL)
	{
		write(1, "\n", 1);
		*command = "exit";
	}
	else if (!*command)
	{
		free (*command);
		return (Off);
	}
	return (On);
}

void	shell_loop(t_minishell *set)
{
	char	*command;

	while (set->run)
	{
		signal(SIGINT, shell_ctrl_c);
		fd_reset(set);
		command = readline(PURPLE">minishell: " WHITE);
		if (!verify(&command))
			continue ;
		add_history(command);
		if (command_parser(set, command) == Off)
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
