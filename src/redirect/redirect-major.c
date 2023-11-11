/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-major.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:06:27 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/11 07:25:56 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_redirect_major(t_minishell *set)
{
	int	fd;

	fd = -1;
	if (!ms_strncmp(set->cmd->name, ">", 1) && set->cmd->next)
	{
		if (access(set->cmd->next->name, F_OK))
			unlink(set->cmd->next->name);
		fd = open(set->cmd->next->name, O_WRONLY | O_CREAT);
	}
	write(fd, "\0", 1);
	close(fd);
}
