/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:16:51 by mister-code       #+#    #+#             */
/*   Updated: 2023/12/22 16:38:21 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_path(t_minishell *set)
{
	t_variable	*var;
	char		*path;
	char		buffer[65535];
	int			i;

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
		*(buffer + ++i) = '\0';
		command_next_last(&set->path, command_push(buffer, Off));
	}
}

void	shell_path_update(t_minishell *set, char *path)
{
	command_pop(&set->path);
	command_next_last(&set->path, command_push(path, Off));
}
