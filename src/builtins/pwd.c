/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:54:28 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/27 10:23:17 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd(t_minishell *set, t_command *cmd, int fd)
{
	(void)set;
	(void)cmd;
	ms_putstr_fd(getcwd(NULL, 0), fd);
	ms_putstr_fd("\n", fd);
	set->status = 0;
}
