/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:27:20 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/27 12:38:56 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_args(t_command *cmd, char *redirect)
{
	int			size;
	t_command	*curr;

	size = 0;
	if (!ms_strncmp(cmd->name, redirect, ms_strlen(redirect)))
	{
		curr = cmd->next->next->next;
		while (curr)
		{
			size++;
			curr = curr->next;
		}
		return (size);
	}
	curr = cmd->next;
	while (curr)
	{
		if (!ms_strncmp(curr->name, redirect, ms_strlen(redirect)))
		{
			curr = curr->next->next;
			continue ;
		}
		size++;
		curr = curr->next;
	}
	return (size);
}
