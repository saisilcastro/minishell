/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:10:20 by mister-code       #+#    #+#             */
/*   Updated: 2023/10/02 17:13:36 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>

t_flag	*flag_push(char *name)
{
	t_flag	*set;

	set = (t_flag *)malloc(sizeof(t_flag));
	if (!set)
		return (NULL);
	set->name = name;
	set->prev = NULL;
	set->next = NULL;
	return (set);
}

void	flag_next_first(t_flag **head, t_flag *set)
{
	if (!set)
		return ;
	set->next = *head;
	if (*head)
		(*head)->prev = set;
	*head = set;
}

void	flag_next_last(t_flag **head, t_flag *set)
{
	t_flag	*last;

	if (!set)
		return ;
	if (*head)
	{
		(*head)->prev = set;
		return ;
	}
	last = *head;
	while (last->next)
	{
		last = last->next;
	}
	set->prev = last;
	last->next = set;
}

void	flag_pop(t_flag *set)
{
	t_flag	*next;

	if (!set)
		return ;
	while (set)
	{
		set->next = next;
		free(set);
		set = next;
	}
}
