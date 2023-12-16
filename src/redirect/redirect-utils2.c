/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:17:24 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/15 10:42:49 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	create_new_list(t_command *original,
	t_command **new, char *command)
{
	char	**arg;
	int		i;

	i = -1;
	arg = NULL;
	*new = NULL;
	if (count_args(original) > 1)
	{
		arg = (char **)malloc((count_args(original) + 1) * sizeof(char *));
		if (!arg)
			return ;
		redirect_argument_get(original, &arg);
	}
	if (!arg)
		command_next_last(new, command_push(command));
	else
		while (arg[++i])
			command_next_last(new, command_push(arg[i]));
	if (arg)
		free_arr(arg);
}

void	builtin_execute(t_minishell *set, t_command *cmd,
		int builtin, char *name_cmd)
{
	t_command	*args;

	create_new_list(cmd, &args, name_cmd);
	if (set->fd_out >= 0)
		set->builtin[builtin - 4](set, args, set->fd_out);
	else
		set->builtin[builtin - 4](set, args, 1);
	command_pop(&args);
}

int	count_redirects(t_command *cmd, char *redirect)
{
	t_command	*curr;
	int			count;

	count = 0;
	curr = cmd;
	while (curr)
	{
		if (!ms_strncmp(curr->name, redirect, ms_strlen(redirect)))
			count++;
		curr = curr->next;
	}
	return (count);
}

t_status	valid_redirect(t_command *cmd)
{
	t_command	*curr;

	curr = cmd;
	while (curr)
	{
		if (!ms_strncmp(curr->name, "<<", 2) || !ms_strncmp(curr->name, ">>", 2)
			|| !ms_strncmp(curr->name, "<", 1)
			|| !ms_strncmp(curr->name, "<", 1))
		{
			if (!curr->next || has_special(curr->next->name[0]))
			{
				error("syntax error near unexpected", NULL, 2);
				return (Off);
			}
		}
		curr = curr->next;
	}
	return (On);
}

t_status	heredoc_is_last(t_command *cmd)
{
	t_command	*curr;
	int			count;

	curr = cmd;
	count = count_redirects(cmd, "<<") + count_redirects(cmd, "<");
	while (count > 1)
	{
		if (!ms_strncmp(curr->name, "<<", 2)
			|| !ms_strncmp(curr->name, "<", 1))
			count--;
		curr = curr->next;
	}
	if (!ms_strncmp(curr->name, "<<", 2))
		return (On);
	return (Off);
}
