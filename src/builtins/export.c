/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:54:25 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/23 11:34:00 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <variable.h>
#include <stdlib.h>
#include <minishell.h>
#include <stdio.h>

void	print_envirolment(void)
{
	extern char	**__environ;

	while (*__environ)
	{
		printf("declare -x %s=\"%s\"\n", get_name(*__environ),
			get_value(*__environ + (ms_strlen(get_name(*__environ)) + 1)));
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

t_variable	*variable_node(char *string)
{
	char		*name;
	char		*value;

	if (!ms_isalpha(string[0]) && string[0] != 95)
	{
		printf("command not found\n");
		exit(0);
	}
	name = get_name(string);
	value = get_value(string + (ms_strlen(name) + 1));
	return (variable_push(name, value));
}

void	export(char *line, t_variable **var)
{
	int		count;
	char	*name;

	count = 0;
	if (line[count] == '\0')
		print_envirolment();
	while (line[count] != '\0')
	{
		while (line[count] && line[count] == ' ')
			count++;
		name = get_name(line + count);
		if (!name)
		{
			printf(PURPLE"minishell: " WHITE "export: "
				"not a valid identifier\n");
			return ;
		}
		if (variable_check(var, name))
			new_value(var, get_name(line + count),
				get_value(line + ((ms_strlen(name) + 1) + count)));
		else
			variable_next_first(var, variable_node(line + count));
		while (line[count] != ' ' && line[count] != '\0')
			count++;
		free(name);
	}
}
