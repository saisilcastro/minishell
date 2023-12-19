/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:50:16 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/18 15:46:25 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_pid	*pid_push(int id)
{
	t_pid	*set;

	set = (t_pid *)malloc(sizeof(t_pid));
	if (!set)
		return (NULL);
	set->id = id;
	set->next = NULL;
	return (set);
}

void	pid_next_first(t_pid **list, t_pid *set)
{
	if (!set)
		return ;
	set->next = *list;
	*list = set;
}

void	pid_next_last(t_pid **list, t_pid *set)
{
	t_pid	*upd;

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

t_pid	*pid_last(t_pid *list)
{
	t_pid	*last;

	last = list;
	while (last->next)
		last = last->next;
	return (last);
}

void	pid_pop(t_pid **list)
{
	t_pid	*next;

	while (*list)
	{
		next = (*list)->next;
		free(*list);
		*list = next;
	}
}
