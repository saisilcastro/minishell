/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:22:39 by mister-code       #+#    #+#             */
/*   Updated: 2023/10/19 23:22:41 by mister-code      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <stdlib.h>

t_echo	*echo_push(char *data)
{
	t_echo	*set;

	set = (t_echo *)malloc(sizeof(t_echo));
	set->data = ms_strdup(data);
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
		if (list->data)
			free(list->data);
		free(list);
		list = next;
	}
}
