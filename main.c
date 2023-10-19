/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:23:18 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/19 09:58:46 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// this is a blood test to see if the new branch has or not been updated

int	main(int argc, char **argv)
{
	t_variable	*var = NULL;
	t_variable	*upd;

	export(argc, argv, var);
	upd = var;
	while (upd)
	{
		printf("%s %s\n", upd->name, upd->value);
		upd = upd->next;
	}
	return (0);
}

void	mine(void)
{
	t_echo		*echo = NULL;
	t_variable	*var = NULL;
	char		*command;

	variable_next_last(&var, variable_push("int", "10"));
	variable_next_last(&var, variable_push("float", "25.2"));
	command = readline("$");
	echo_parse(&echo, var, command);
	echo_execute(echo, Off);
	echo_pop(echo);
	free(command);
}
