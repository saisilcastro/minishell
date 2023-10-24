/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command-parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:33:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/23 14:54:09 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>
#include <common.h>
#include <stdio.h>

void	command_parser(t_command **list, char *command)
{
	char	buffer[1024];
	int		i;

	while (*command)
	{
		while (*command && has_space(*command))
			command++;
		i = 0;
		while (*command && !has_space(*command))
			*(buffer + i++) = *command++;
		*(buffer + i) = '\0';
		command_next_last(list, command_push(buffer));
		if (!*command)
			break ;
		command++;
	}
}
