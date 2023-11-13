/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle-quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:19:28 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/13 15:19:38 by lde-cast         ###   ########.fr       */
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
	if (!quotes_is_closed(list->name + index, list->name[index], set, Off))
		return ;
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
