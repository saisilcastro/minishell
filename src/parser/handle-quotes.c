/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle-quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:19:28 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/16 17:35:11 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_quotes(t_command *list, t_minishell *set, char c)
{
	char	copy[40000];
	int		index;
	int		index2;

	index = -1;
	while (list->name[++index] && list->name[index] != c)
		copy[index] = list->name[index];
	index2 = index;
	while (list->name[++index2] && list->name[index2] != c)
	{
		copy[index] = list->name[index2];
		index++;
	}
	while (list->name[++index2] && list->name[index2] != '\0')
	{
		copy[index] = list->name[index2];
		index++;
	}
	copy[index] = '\0';
	free (list->name);
	list->name = ms_strdup(copy);
}

void	remove_quotes(t_command *list, t_minishell *set)
{
	int	index;

	index = 0;
	if (!list->name || !*list->name)
		return ;
	while (list->name && list->name[index])
	{
		if (list->name[index] && list->name[index] == '\'')
		{
			index++;
			while (list->name[index + 1] && list->name[index + 1] != '\'')
				index++;
			update_quotes(list, set, '\'');
		}
		else if (list->name[index] && list->name[index] == '"')
		{
			index++;
			while (list->name[index + 1] && list->name[index + 1] != '"')
				index++;
			update_quotes(list, set, '"');
		}
		if (list->name[index] && list->name[index] != '\''
			&& list->name[index] != '"')
			index++;
	}
}

t_status	quotes_is_closed(char *command, char c,
	t_minishell *set, t_status msg)
{
	int	index;

	index = 0;
	while (command && command[++index])
	{
		if (command[index] == c)
			return (On);
	}
	if (msg == On)
		error_and_clear(set, "Unclosed quotes in the string.");
	return (Off);
}

int	handle_quotes(char *command, char *buffer, t_minishell *set)
{
	int	index;
	int	index2;

	index = 0;
	index2 = 0;
	while (command && command[index] && !has_space(command[index])
		&& !has_special(command[index]))
	{
		if (command[index] == '\'' || (command[index] == '\"'
				&& command[index - 1] != '\\'))
		{
			if (!quotes_is_closed(command + index, command[index], set, On))
				return (-1);
			symbol_remaider(command + index, buffer, &index2, command[index]);
			index += upd_index(command + (index + 1), command[index]) + 1;
			if (!command[index])
				break ;
		}
		else
			*(buffer + index2++) = command[index];
		index++;
	}
	*(buffer + index2) = '\0';
	return (index);
}
