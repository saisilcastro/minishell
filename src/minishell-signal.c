/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:52:25 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/28 15:54:36 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		ms_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line ("", 0);
		rl_redisplay();
	}
}

void	shell_execute_ctrl_c(int signal)
{
	(void)signal;
	ms_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line ("", 0);
}

void	heredoc_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line ("", 0);
		rl_redisplay();
		shell_get()->run_hdoc = Off;
		shell_get()->status = 130;
		close(STDIN_FILENO);
	}
}

void	shell_ctrl_backslash(int signal)
{
	(void)signal;
}

int	ft_check_if_signaled(void)
{
	int	wstatus;

	wstatus = shell_get()->status;
	if (WIFSIGNALED(wstatus) && wstatus != 13)
	{
		wstatus = WTERMSIG(wstatus);
		if (wstatus == 2)
			shell_get()->status = 130;
		return (1);
	}
	return (0);
}
