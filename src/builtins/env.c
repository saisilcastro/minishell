/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:17:29 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/27 10:15:34 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	env(t_minishell *set, t_command *cmd, int fd)
{
	extern char	**__environ;
	int			i;

	(void)cmd;
	i = -1;
	while (*(__environ + ++i))
	{
		ms_putstr_fd(*(__environ + i), fd);
		ms_putstr_fd("\n", fd);
	}
	set->status = 0;
}
