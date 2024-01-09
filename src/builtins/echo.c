/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:22:39 by mister-code       #+#    #+#             */
/*   Updated: 2023/12/21 12:07:54 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	skip_newline(t_command **cmd, t_status *newline)
{
	t_command	*upd;
	int			i;

	if (*cmd)
	{
		upd = *cmd;
		while (upd)
		{
			i = 0;
			while (upd->name[i] && has_space(upd->name[i]))
				i++;
			if (upd->name[i++] == '-')
			{
				while (upd->name[i] && upd->name[i] == 'n')
					i++;
				if (!upd->name[i])
				{
					*newline = Off;
					*cmd = upd->next;
				}
			}
			upd = upd->next;
		}
	}
}

void	echo_execute(t_minishell *set, t_command *cmd, int fd)
{
	t_command	*upd;
	t_status	newline;

	newline = On;
	if (!cmd)
		return ;
	upd = cmd->next;
	skip_newline(&upd, &newline);
	while (upd)
	{
		ms_putstr_fd(upd->name, fd);
		if (upd->name[0] != ' ' && upd->next)
			ms_putstr_fd(" ", fd);
		if (upd->next == NULL)
		{
			ms_putstr_fd("\0", fd);
			break ;
		}
		upd = upd->next;
	}
	if (newline)
		ms_putstr_fd("\n", fd);
	set->status = 0;
}
