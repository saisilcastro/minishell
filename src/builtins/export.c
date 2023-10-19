/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 09:54:25 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/19 14:51:13 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <variable.h>
#include <stdlib.h>
#include <stdio.h>

static char	*get_value(char *string)
{
	int		index;
	char	value[256];

	index = 0;
	if (string[0] == '"')
	{
		index = 1;
		while (string[index] != '"')
		{
			value[index] = string[index];
			index++;
		}
	}
	else
		while (string[index++])
			value[index] = string[index];
	value[index] = '\0';
	printf("%s\n", value);
	return (NULL);
}

static t_variable	*variable_node(char *string)
{
	char		name[256];
	char		*value;
	int			index;
	t_status	*new;

	value = NULL;
	index = -1;
	while (string[++index] && string[index] != '=')
		name[index] = string[index];
	name[index] = '\0';
	value = get_value(string + (index + 1));
	return (variable_push(name, value));
}

void	export(int argc, char **argv, t_variable *var)
{
	int	index;

	index = 2;
	while (argc-- > 2)
		variable_next_first(&var, variable_node(argv[index++]));
}
