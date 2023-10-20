/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo-next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:53:02 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/18 15:34:54 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins/echo.h>

void	echo_next_last(t_echo **list, t_echo *set)
{
	t_echo	*update;

	if (!*list)
	{
		*list = set;
		return ;
	}
	update = *list;
	while (update->next)
		update = update->next;
	update->next = set;
}
