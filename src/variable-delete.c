/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable-delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:42:43 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/10 12:11:51 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	variable_delete(t_variable **list, char *name)
{
	t_variable	*curr;
	t_variable	*next;

	curr = *list;
	if (!curr->next->next)
	{
		curr->next = NULL;
		return ;
	}
	while (curr)
	{
		if (!ms_strncmp(curr->next->name, name, ms_strlen(name)))
		{
			next = curr->next;
			curr->next = curr->next->next;
			if (next->name)
				free(next->name);
			if (next->value)
				free(next->value);
			free(next);
			return ;
		}
		curr = curr->next;
	}
}

void	node_delete(t_command **cmd, char *name)
{
	t_command	*curr;
	t_variable	*next;

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
