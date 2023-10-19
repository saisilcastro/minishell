/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:23:18 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/19 14:51:50 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>

void	mine(void);

int	main(int argc, char **argv)
{
	mine();
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
	echo_execute(echo, On);
	echo_pop(echo);
	variable_pop(var);
	free(command);
}
