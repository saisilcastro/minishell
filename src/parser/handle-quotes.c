/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle-quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:19:28 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/22 12:12:26 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	update_quotes(t_command *list, char c, int p)
{
	char	copy[40000];
	int		index;
	int		index2;

	index = -1;
	while (list->name[++index] && index < p)
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

void	remove_quotes(t_command *list)
{
	int	i;
	int	temp;

	i = 0;
	while (list->name && list->name[i])
	{
		if (list->name[i] && list->name[i] == '\'')
		{
			temp = i;
			i++;
			while (list->name[i + 1] && list->name[i + 1] != '\'')
				i++;
			update_quotes(list, '\'', temp);
		}
		else if (list->name[i] && list->name[i] == '"')
		{
			temp = i;
			i++;
			while (list->name[i + 1] && list->name[i + 1] != '"')
				i++;
			update_quotes(list, '"', temp);
		}
		if (list->name[i] && list->name[i] != '\'' && list->name[i] != '"')
			i++;
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
		if (command[index] && (command[index] == '\''
				|| command[index] == '\"'))
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
