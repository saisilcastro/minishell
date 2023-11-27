/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:17:24 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/27 15:24:38 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	create_new_list(t_command *original,
	t_command **new, char *redirect)
{
	char	**arg;
	int		i;

	i = 0;
	*new = NULL;
	redirect_argument_get(original, &arg, redirect);
	if (!arg)
	{
		if (!ms_strncmp(original->name, redirect, ms_strlen(redirect)))
			command_next_last(new, command_push(original->next->next->name));
		else
			command_next_last(new, command_push(original->name));
		return ;
	}
	while (arg[i])
	{
		command_next_last(new, command_push(arg[i]));
		i++;
	}
}

t_status	open_fd(int *fd, char *redirect, char *name, t_minishell *set)
{
	if (!set->cmd->next->next || (shell_index(set, set->cmd->next->next,
				Off) == 7 && set->cmd->next->next->next) || (shell_index(set,
				set->cmd->next->next, Off) == 9 && set->cmd->next->next->next))
	{
		if (!ms_strncmp(redirect, ">>", 2))
			*fd = open(redirect_file(set->cmd, ">>")->name,
					O_APPEND | O_CREAT, 00700);
		else
			*fd = open(name, O_CREAT | O_TRUNC, 00700);
		return (Off);
	}
	else if (!ms_strncmp(redirect, ">>", 2))
	{
		*fd = open(name, O_WRONLY | O_APPEND | O_CREAT, 00700);
		if (*fd == -1)
			return (Off);
	}
	else
	{
		*fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 00700);
		if (*fd == -1)
			return (Off);
	}
	return (On);
}

void	builtin_execute(t_minishell *set, int builtin, char *redirect, int fd)
{
	t_command	*args;

	create_new_list(set->cmd, &args, redirect);
	set->builtin[builtin - 4](set, args, fd);
	close(fd);
	command_pop(&args);
}
