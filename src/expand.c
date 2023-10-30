/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:48:22 by lumedeir          #+#    #+#             */
/*   Updated: 2023/10/29 13:07:11 by mister-code      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

static void	update_quotes(t_command *list)
{
	char	copy[40000];
	int		index;
	int		index2;

	index = -1;
	while (list->name[++index] && list->name[index] != '\'')
		copy[index] = list->name[index];
	index2 = index + 1;
	while (list->name[index2] && list->name[index2] != '\'')
	{
		copy[index] = list->name[index2++];
		index++;
	}
	index2 += 1;
	while (list->name[index2])
	{
		copy[index] = list->name[index2];
		index++;
		index2++;
	}
	copy[index] = '\0';
	free (list->name);
	list->name = ms_strdup(copy);
}

static void	update(t_command *list, char *value, int size)
{
	char	copy[40000];
	int		index;
	int		index2;

	index = -1;
	while (list->name[++index] && list->name[index] != '$')
		copy[index] = list->name[index];
	index2 = index + size + 1;
	while (value && *value)
	{
		copy[index] = *value++;
		index++;
	}
	while (list->name[index2])
	{
		copy[index] = list->name[index2];
		index++;
		index2++;
	}
	copy[index] = '\0';
	free (list->name);
	list->name = ms_strdup(copy);
}

static void	expand(t_command *list, t_variable *var)
{
	t_variable	*curr_var;
	int			index;

	index = 0;
	while (list->name[index])
	{
		while (list->name[index] && list->name[index] != '$')
			index++;
		curr_var = var;
		if (list->name && list->name[index] == '$')
		{
			while (curr_var)
			{
				if (!ms_strncmp(list->name + (index + 1),
						curr_var->name, ms_strlen(curr_var->name)))
				{
					update(list, curr_var->value, ms_strlen(curr_var->name));
					index = -1;
					break ;
				}
				curr_var = curr_var->next;
			}
			index++;
		}
	}
}

void	expansion(t_command **list, t_variable *var)
{
	t_command	*current;
	int			count;

	current = *list;
	count = 0;
	while (current)
	{
		if (ms_strchr(current->name, '\''))
			update_quotes(current);
		else if (ms_strchr(current->name, '$'))
			expand(current, var);
		current = current->next;
	}
}
