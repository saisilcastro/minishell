/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:09:46 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/21 10:28:23 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_status	has_digit(char *str)
{
	char	*upd;

	upd = str;
	if (*upd == '+' || *upd == '-')
		upd++;
	while (*upd && ms_isdigit(*upd))
		upd++;
	if (!*upd)
		return (On);
	return (Off);
}

void	exit_fn(t_minishell *set, t_command *cmd, int fd)
{
	int		max;
	long	status;

	(void)set;
	(void)fd;
	status = 0;
	max = command_size(cmd);
	if (max > 2)
	{
		ms_putstr_fd("exit: too many arguments\n", 2);
		exit(1);
	}
	if (max == 2)
	{
		if (!has_digit(cmd->next->name)
			|| ms_atol(cmd->next->name) > __INT_MAX__
			|| ms_atol(cmd->next->name) < -((long)__INT_MAX__ + 1))
		{
			ms_putstr_fd("exit: numeric argument required\n", 2);
			exit(2);
		}
		status = (unsigned char)ms_atol(cmd->next->name);
	}
	exit(status);
}
