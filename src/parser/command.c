/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:24:00 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/15 17:02:56 by lumedeir         ###   ########.fr       */
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
	set->flag_quotes = Off;
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

void command_show(t_command *cmd, int fd)
{
	t_command *upd = cmd;
	while(upd)
	{
		ms_putstr_fd(upd->name, fd);
		ms_putstr_fd("\n", fd);
		upd = upd->next;
	}
}