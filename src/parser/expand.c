/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:48:22 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/22 12:48:11 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	upd_line(t_command *list, int *index)
{
	int		i;
	int		j;
	char	copy[65535];

	i = 0;
	while (list->name && list->name[i] && i < *index)
	{
		copy[i] = list->name[i];
		i++;
	}
	j = i + 1;
	while (list->name && list->name[i])
	{
		copy[i] = list->name[j];
		j++;
		i++;
	}
	*index += 1;
	copy[i] = '\0';
	free (list->name);
	list->name = ms_strdup(copy);
}

static void	do_expansion(t_command *list, int *index,
	t_variable *var, t_minishell *set)
{
	if (list->name[*index] == '$' && list->name[*index + 2]
		&& (list->name[*index + 1] == '"'
			|| list->name[*index + 1] == '\''))
		upd_line(list, index);
	else
		*index += 1;
	while (list->name[*index] && list->name[*index] != '"')
	{
		if (list->name[*index] == '$' && (list->name[*index + 1] == 0x5F
				|| ms_isalpha(list->name[*index + 1])
				|| list->name[*index + 1] == 0x3F))
		{
			find_variable(list, var, (*index + 1), set);
			*index = 0;
			break ;
		}
		*index += 1;
	}
}

static void	find_signal(t_command *lst, t_variable *var,
	t_minishell *set)
{
	int	i;

	i = 0;
	while (lst->name && lst->name[i])
	{
		if (lst->name[i] == '\'' && lst->name[i + 1])
			i += (upd_index(lst->name + (i + 1), '\'') + 2);
		else if ((lst->name[i] == '\"' && lst->name[i + 1])
			|| (lst->name[i] == '$' && (lst->name[i + 1] == '"'
					|| lst->name[i + 1] == '\'')))
			do_expansion(lst, &i, var, set);
		if (lst->name[i] && lst->name[i + 1] && lst->name[i] == '$'
			&& (ms_isalpha(lst->name[i + 1])
				|| lst->name[i + 1] == '_' || lst->name[i + 1] == '?'))
		{
			find_variable(lst, var, (i + 1), set);
			i = 0;
			continue ;
		}
		if ((lst->name[i] == '"' || lst->name[i] == '\'')
			&& !lst->name[i + 1])
			i++;
		else if (lst->name[i] && lst->name[i] != '\'' && lst->name[i] != '"')
			i++;
	}
}

void	expansion(t_command **list, t_variable *var, t_minishell *set)
{
	t_command	*current;

	if (!*list)
		return ;
	current = *list;
	while (current)
	{
		if (current->name && ms_strchr(current->name, '$'))
			find_signal(current, var, set);
		if (ms_strchr(current->name, '\'') || ms_strchr(current->name, '"'))
		{
			current->flag_quotes = On;
			remove_quotes(current);
		}
		current = current->next;
	}
}
