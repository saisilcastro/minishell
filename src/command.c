/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:24:00 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/31 12:43:54 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*command_push(char *name)
{
	t_command	*set;

	set = (t_command *)malloc(sizeof(t_command));
	if (!set)
		return (NULL);
	set->name = ms_strdup(name);
	set->next = NULL;
	return (set);
}

void	command_next_last(t_command **list, t_command *set)
{
	t_command	*upd;

	if (!*list)
	{
		*list = set;
		return ;
	}
	upd = *list;
	while (upd->next)
		upd = upd->next;
	upd->next = set;
}

void	command_pop(t_command **list)
{
	t_command	*next;

	while (*list)
	{
		next = (*list)->next;
		if ((*list)->name)
			free((*list)->name);
		free(*list);
		*list = next;
	}
}
