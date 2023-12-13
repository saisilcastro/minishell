/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable-next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:18:28 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/13 11:00:04 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	variable_next_first(t_variable **head, t_variable *set)
{
	if (!set)
		return ;
	if (*head)
		set->next = *head;
	*head = set;
}

void	var_next_last(t_variable **head, t_variable *set)
{
	t_variable	*update;

	if (!*head)
	{
		*head = set;
		return ;
	}
	update = *head;
	while (update->next)
		update = update->next;
	update->next = set;
}
