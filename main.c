/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:23:18 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/18 13:16:45 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <variable.h>
#include <stdio.h>

int	main(void)
{
	return (0);
}

void	test()
{
	t_variable	*var = NULL;
	t_variable	*update;

	variable_next_first(&var, variable_push("test", "5"));
	variable_next_first(&var, variable_push("float", "15.8"));
	update = var;
	while (update)
	{
		printf("%s %s\n", update->name, update->value);
		update = update->next;
	}
	variable_pop(var);
}