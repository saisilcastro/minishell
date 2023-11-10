/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:25:22 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/08 16:41:28 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	control_c(int signal)
{
}

static void	control_nothing(int signal)
{
}

void	shell_set(t_minishell *set)
{
	if (!set)
		return ;
	set->cmd = NULL;
	set->var = NULL;
	set->file = NULL;
	set->status = 0;
	//signal(SIGINT, control_c);
	signal(SIGQUIT, control_nothing);
	environment_push(set);
	variable_next_first(&set->var, variable_push("test", "Olá"));
	variable_next_first(&set->var, variable_push("test2", "Mundo!!"));
}

void	shell_pop(t_minishell *set)
{
	if (!set)
		return ;
	variable_pop(set->var);
	if (set->cmd)
		command_pop(&set->cmd);
	if (set->file)
		command_pop(&set->file);
	rl_clear_history();
}
