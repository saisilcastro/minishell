/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:37:44 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/22 12:09:54 by lumedeir         ###   ########.fr       */
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

void	argument_get(t_command *last, char ***arg)
{
	t_command	*upd;
	int			i;

	if (!command_size(last))
	{
		*arg = NULL;
		return ;
	}
	*arg = (char **)malloc((command_size(last) + 2) * sizeof(char *));
	if (!*arg)
		return ;
	*(*arg + 0) = ms_strdup("fucker");
	i = 1;
	upd = last;
	while (upd)
	{
		*(*arg + i) = ms_strdup(upd->name);
		upd = upd->next;
		i++;
	}
	*(*arg + i) = NULL;
}
