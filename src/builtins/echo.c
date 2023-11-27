/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:22:39 by mister-code       #+#    #+#             */
/*   Updated: 2023/11/27 10:17:24 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	skip_newline(t_command **cmd, t_status *newline)
{
	int	size;
	int	i;

	if (*cmd && !ms_strncmp((*cmd)->name, "-n", 2))
	{
		while (*cmd)
		{
			size = ms_strlen((*cmd)->name);
			i = 1;
			while (i < size)
			{
				if ((*cmd)->name[i] != 'n')
					return ;
				i++;
			}
			*newline = Off;
			*cmd = (*cmd)->next;
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
