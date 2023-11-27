/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:37:44 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/27 13:50:23 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_command	*redirect_file(t_command *cmd, char *redirect)
{
	t_command	*curr;

	curr = cmd;
	while (curr)
	{
		if (!ms_strncmp(curr->name, redirect, ms_strlen(redirect)))
			return (curr->next);
		curr = curr->next;
	}
	return (NULL);
}

t_status	search_path(t_command *env, t_command *app, char *path)
{
	t_command	*upd;
	int			i;
	int			j;

	upd = env;
	while (upd)
	{
		i = -1;
		while (*(upd->name + ++i))
			*(path + i) = *(upd->name + i);
		*(path + i++) = '/';
		j = -1;
		while (*(app->name + ++j))
			*(path + i++) = *(app->name + j);
		*(path + i) = '\0';
		if (!access(path, F_OK))
			break ;
		else
			i = 0;
		upd = upd->next;
	}
	*(path + i) = '\0';
	return (i);
}

static void	redirect_middle(t_command *cmd, char ***arg, char *redirect)
{
	t_command	*curr;
	int			i;

	if (command_size(cmd) == 3)
	{
		*arg = NULL;
		return ;
	}
	curr = cmd->next;
	*arg = (char **)malloc((count_args(cmd, redirect) + 2) * sizeof(char *));
	if (!*arg)
		return ;
	*(*arg + 0) = ms_strdup(cmd->name);
	i = 1;
	while (curr)
	{
		if (!ms_strncmp(curr->name, redirect, ms_strlen(redirect)))
		{
			curr = curr->next->next;
			continue ;
		}
		*(*arg + i++) = ms_strdup(curr->name);
		curr = curr->next;
	}
	*(*arg + i) = NULL;
}

static void	redirect_first(t_command *cmd, char ***arg, char *redirect)
{
	t_command	*curr;
	int			size;
	int			i;

	if (command_size(cmd) == 3)
	{
		*arg = NULL;
		return ;
	}
	curr = cmd->next->next->next;
	size = 0;
	*arg = (char **)malloc((count_args(cmd->next->next, redirect) + 2)
			* sizeof(char *));
	if (!*arg)
		return ;
	*(*arg + 0) = ms_strdup(cmd->name);
	i = 1;
	curr = cmd->next->next->next;
	while (curr)
	{
		*(*arg + i++) = ms_strdup(curr->next->next->name);
		curr = curr->next;
	}
	*(*arg + i) = NULL;
}

void	redirect_argument_get(t_command *cmd, char ***arg, char *redirect)
{
	if (!ms_strncmp(cmd->name, redirect, ms_strlen(redirect)))
		redirect_first(cmd, arg, redirect);
	else
		redirect_middle(cmd, arg, redirect);
}
