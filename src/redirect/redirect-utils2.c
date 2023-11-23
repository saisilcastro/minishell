/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:17:24 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/23 20:56:58 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_status	is_valid_argument(t_minishell *set, int i, char *redirect)
{
	t_command	*curr;
	int			count_arg;
	int			fd;

	curr = set->cmd;
	count_arg = count_args(set->cmd, redirect);
	if (count_arg >> 0 && (i == 7 || i == 9))
	{
		if (!ms_strncmp(">", redirect, 1))
		{
			fd = open(redirect_file(set->cmd, ">")->name,
					O_WRONLY | O_CREAT | O_TRUNC, 00700);
			if (fd == -1)
				return (0);
			close (fd);
		}
		if (i == 9)
			ms_putstr_fd("env: No such file or directory\n", 2);
		return (Off);
	}
	return (On);
}

static t_status	open_fd(int fd, char *redirect, char *name)
{
	if (!ms_strncmp(redirect, ">>", 2))
	{
		fd = open(name, O_WRONLY | O_APPEND | O_CREAT, 00700);
		if (fd == -1)
			return (Off);
	}
	else
	{
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 00700);
		if (fd == -1)
			return (Off);
	}
	return (On);
}

static void	create_new_list(t_command *original, t_command *new, char *redirect)
{
	char	**arg;
	int		i;

	i = 0;
	new = NULL;
	argument_get(original, &arg, redirect);
	if (!arg)
	{
		if (!ms_strncmp(original->name, redirect, ms_strlen(redirect)))
			command_next_last(&new, command_push(original->next->next->name));
		else
			command_next_last(&new, command_push(original->name));
		return ;
	}
	while (arg[i])
	{
		command_next_last(&new, command_push(arg[i]));
		i++;
	}
}

void	bulting_execute(t_minishell *set, int bulting, char *redirect)
{
	int			pid;
	t_command	args;
	int			fd;

	if (!is_valid_argument(set, bulting, redirect))
		return ;
	if (!open_fd(fd, redirect, redirect_file(set->cmd, redirect)->name))
		return ;
	create_new_list(set->cmd, &args, redirect);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		set->builtin[bulting - 4](set, &args);
		ms_putstr_fd("*******************here", 2);
	}
	else
		waitpid(pid, NULL, 0);
	close(fd);
}
