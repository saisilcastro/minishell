/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable-delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:42:43 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/18 13:06:04 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <variable.h>

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
