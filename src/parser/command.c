/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:24:00 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/28 16:43:39 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*command_push(char *name, t_status flag)
{
	t_command	*set;

	if (!name || !*name)
		return (NULL);
	set = (t_command *)malloc(sizeof(t_command));
	if (!set)
		return (NULL);
	set->name = ms_strdup(name);
	set->flag_quotes = flag;
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

int	command_size(t_command *list)
{
	t_command	*upd;
	int			size;

	size = 0;
	upd = list;
	while (upd)
	{
		size++;
		upd = upd->next;
	}
	return (size);
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

void	command_pop_first(t_command **head)
{
	t_command	*next;

	if (head && *head)
	{
		next = (*head)->next;
		if ((*head)->name)
			free((*head)->name);
		free(*head);
		*head = next;
	}
}
