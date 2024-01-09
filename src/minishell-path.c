/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:16:51 by mister-code       #+#    #+#             */
/*   Updated: 2024/01/08 12:00:10 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_path(t_minishell *set)
{
	t_variable	*var;
	char		*path;
	char		buffer[65535];
	int			i;

	ms_memset(buffer, '\0', 65535);
	var = var_search(set->var, "PATH");
	if (var)
	{
		i = -1;
		path = var->value;
		while (*path)
		{
			if (*path == ':')
			{
				*(buffer + ++i) = '\0';
				command_next_last(&set->path, command_push(buffer, Off));
				path++;
				i = -1;
			}
			*(buffer + ++i) = *path;
			path++;
		}
	}
	command_next_last(&set->path, command_push(buffer, Off));
}

void	shell_path_update(t_minishell *set, char *path)
{
	command_pop(&set->path);
	command_next_last(&set->path, command_push(path, Off));
}
