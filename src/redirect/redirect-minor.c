/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-minor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:05:10 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/20 22:54:07 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	open_if_exists(char *path)
{
	int	fd;

	fd = open(path, O_WRONLY, 0777);
	if (fd == -1)
	{
		ms_putstr_fd("minishell: ", 2);
		ms_putstr_fd(path, 2);
		ms_putstr_fd(": no such file or directory\n", 2);
	}
	close(fd);
}

void	shell_redirect_minor(t_minishell *set)
{
	if (!ms_strncmp(set->cmd->name, "<", 1))
		open_if_exists(set->cmd->next->name);
}
