/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo-parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:39:20 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/19 22:59:21 by mister-code      ###   ########.fr       */
=======
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:39:20 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/19 18:00:20 by lde-cast         ###   ########.fr       */
>>>>>>> 3f4fbd6ebadf898171379d0b2401ff166fcedf75
/*                                                                            */
/* ************************************************************************** */

#include <builtins/echo.h>
#include <stdio.h>

static char	*has_variable(t_echo **set, t_variable *var, char *command);
static char	*has_word(t_echo **set, char *command);

void	echo_parse(t_echo **set, t_variable *var, char *command)
{
	char	*update;
	int		i;

	update = command;
	i = 0;
	while (*update)
	{
		update = has_variable(set, var, update);
		update = has_word(set, update);
<<<<<<< HEAD
		if (*update && *command != '$')
=======
		if (*update)
>>>>>>> 3f4fbd6ebadf898171379d0b2401ff166fcedf75
			update++;
	}
}

static char	*load_word(char *buffer, char *command, int *i, char c)
{
	*i = 0;
	command++;
	while (*command && *command != c)
	{
		*(buffer + *i) = *command++;
		*i += 1;
	}
	*(buffer + *i) = '\0';
<<<<<<< HEAD
	command++;
=======
>>>>>>> 3f4fbd6ebadf898171379d0b2401ff166fcedf75
	return (command);
}

static char	*has_word(t_echo **set, char *command)
{
	char	buffer[65535];
	int		i;

	i = 0;
	if (*command)
	{
		if (*command == '\"')
			command = load_word(buffer, command, &i, '\"');
		else if (*command == '\'')
			command = load_word(buffer, command, &i, '\'');
		if (i)
		{
			echo_next_last(set, echo_push(buffer));
<<<<<<< HEAD
			if (*command == ' ')
				echo_next_last(set, echo_push(" "));
=======
>>>>>>> 3f4fbd6ebadf898171379d0b2401ff166fcedf75
		}
	}
	return (command);
}

static char	*has_variable(t_echo **set, t_variable *var, char *command)
{
	t_variable	*local;
	char		buffer[65535];
	int			i;

<<<<<<< HEAD
	if (*command && *command == '$')
=======
	if (*command == '$')
>>>>>>> 3f4fbd6ebadf898171379d0b2401ff166fcedf75
	{
		i = 0;
		command++;
		while (*command && !has_space(*command))
		{
			*(buffer + i++) = *command;
			command++;
		}
		*(buffer + i) = '\0';
		local = variable_search(var, buffer);
		if (local)
			echo_next_last(set, echo_push(local->value));
<<<<<<< HEAD
		if (*command == ' ')
			echo_next_last(set, echo_push(" "));
=======
>>>>>>> 3f4fbd6ebadf898171379d0b2401ff166fcedf75
	}
	return (command);
}
