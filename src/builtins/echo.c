/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:06:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/18 16:46:37 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

t_echo	*echo_push(char *data)
{
	t_echo	*set;

	set = (t_echo *)malloc(sizeof(t_echo));
	set->data = data;
	set->next = NULL;
	return (set);
}

void	echo_execute(t_echo *set, t_status newline)
{
	t_echo	*update;

	update = set;
	while (update)
	{
		printf("%s", update->data);
		update = update->next;
	}
	if (newline)
		printf("\n");
}

void	echo_pop(t_echo *list)
{
	t_echo	*next;

	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}
