/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:16:51 by mister-code       #+#    #+#             */
/*   Updated: 2023/11/13 11:45:07 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_path(t_minishell *set)
{
	t_variable	*var;
	char		*path;
	char		buffer[65535];
	int			i;

	var = variable_search(set->var, "PATH");
	if (var)
	{
		i = -1;
		path = var->value;
		while (*path)
		{
			if (*path == ':')
			{
				*(buffer + ++i) = '\0';
				command_next_last(&set->path, command_push(buffer));
				path++;
				i = -1;
			}
			*(buffer + ++i) = *path;
			path++;
		}
	}
}
