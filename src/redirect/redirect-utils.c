/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:37:44 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/28 16:15:35 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_status	search_path(t_command *env, t_command *app, char *path)
{
	t_command	*upd;
	int			i;
	int			j;

	upd = env;
	i = 0;
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

void	redirect_argument_get(t_command *cmd, char ***arg)
{
	t_command	*curr;
	int			i;

	i = 0;
	curr = cmd;
	while (curr)
	{
		if (has_redirect(curr))
		{
			curr = curr->next->next;
			while (curr && !has_redirect(curr))
			{
				*(*arg + i++) = ms_strdup(curr->name);
				curr = curr->next;
			}
		}
		else if (curr)
		{
			*(*arg + i++) = ms_strdup(curr->name);
			curr = curr->next;
		}
	}
	*(*arg + i) = NULL;
}

char	*get_name(char *line)
{
	char	name[5000];
	int		index;

	index = -1;
	while (line && line[++index] && line[index] != ' ')
		name[index] = line[index];
	name[index] = '\0';
	return (ms_strdup(name));
}

t_status	open_redirects(t_minishell *set, t_command *cmd)
{
	t_command	*upd;

	upd = cmd;
	while (upd)
	{
		if (!upd->flag_quotes && (!ms_strncmp(upd->name, "<<", 2)
				|| !ms_strncmp(upd->name, "<", 1)))
		{
			if (get_infile(set, upd) == Off)
				return (Off);
		}
		else if (!upd->flag_quotes && (!ms_strncmp(upd->name, ">>", 1)
				|| !ms_strncmp(upd->name, ">", 1)))
		{
			if (set->fd_out >= 0)
			{
				close(set->fd_out);
				set->fd_out = -3;
			}
			open_fds(set, upd->name, upd->next->name);
		}
		upd = upd->next;
	}
	return (On);
}
