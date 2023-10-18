/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:23:18 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/18 16:59:07 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// this is a blood test to see if the new branch has or not been updated

int	main(void)
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
	return (0);
}
