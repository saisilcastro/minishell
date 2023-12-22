/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:32:34 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/22 11:33:18 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	upd_index(char *command, char c)
{
	int	index;

	index = 0;
	if (!command)
		return (0);
	while (command[index] && command[index] != c)
		index++;
	return (index);
}

void	symbol_remaider(char *command, char *buffer, int *i, char c)
{
	int	index;

	index = 1;
	if (!command || command[1] == c)
	{
		if (command[2] == ' ')
		{
			*(buffer + *i) = ' ';
			*i += 1;
		}
		return ;
	}
	*(buffer + *i) = command[0];
	*i += 1;
	while (command[index] && command[index] != c)
	{
		*(buffer + *i) = command[index];
		*i += 1;
		index++;
	}
	*(buffer + *i) = command[index];
	*i += 1;
}
