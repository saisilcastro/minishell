/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:54:25 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/20 11:25:27 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <variable.h>
#include <stdlib.h>
#include <minishell.h>
#include <stdio.h>

static void	print_envirolment(void)
{
	extern char	**__environ;

	while (*__environ)
	{
		printf("%s\n", *__environ);
		__environ++;
	}
}

static int	variable_check(t_variable **var, char *string)
{
	t_variable	*curr;

	curr = *var;
	while (curr)
	{
		if (ms_strcmp(curr->name, string))
			return (1);
		curr = curr->next;
	}
	return (0);
}

static void	new_value(t_variable **var, char *string, char *number)
{
	t_variable	*curr;

	curr = *var;
	while (curr && !ms_strcmp(curr->name, string))
		curr = curr->next;
	free(curr->value);
	curr->value = number;
}

void	export(int argc, char **argv, t_variable **var)
{
	int		index;
	char	*name;

	index = 2;
	if (argc == 2 && ms_strcmp(argv[1], "export"))
		print_envirolment();
	while (argc-- > 2)
	{
		name = get_name(argv[index]);
		if (variable_check(var, name))
			new_value(var, get_name(argv[index]),
				get_value(argv[index] + (ms_strlen(name) + 1)));
		else
			variable_next_first(var, variable_node(argv[index++]));
		free(name);
	}
}
