/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:17:29 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/28 19:23:18 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	env(t_minishell *set, t_command *cmd, int fd)
{
	t_variable	*var;

	(void)cmd;
	var = set->var;
	while (var)
	{
		if (ms_strlen(var->value))
		{	
			ms_putstr_fd(var->name, fd);
			ms_putstr_fd("=", fd);
			ms_putstr_fd(var->value, fd);
			ms_putstr_fd("\n", fd);
		}
		var = var->next;
	}
	set->status = 0;
}
