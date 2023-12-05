/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:37:44 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/05 16:42:23 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
