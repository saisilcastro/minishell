/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable-delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:42:43 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/02 12:26:47 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	variable_delete(t_variable **list, char *name)
{
	t_variable	*update;

	update = *list;
	while (update)
	{
		if (ms_strcmp(update->name, name))
		{
			update->value = "";
			return ;
		}
		update = update->next;
	}
}

void	node_delete(t_command **cmd, char *name)
{
	t_command	*curr;

	curr = *cmd;
	if (!curr->next->next)
	{
		curr->next = NULL;
		return ;
	}
	while (curr)
	{
		if (!ms_strncmp(curr->next->name, name, ms_strlen(name)))
		{
			curr->next = curr->next->next;
			return ;
		}
		curr = curr->next;
	}
}
