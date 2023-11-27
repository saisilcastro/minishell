/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:03:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/27 15:38:24 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	name_copy(t_command *upd, char *buffer, int *j)
{
	int	i;

	i = -1;
	while (*(upd->name + ++i))
	{
		*j += 1;
		*(buffer + *j) = *(upd->name + i);
	}
}

void	pipe_extract(t_minishell *set, t_command **pipe)
{
	t_command	*upd;
	char		buffer[65535];
	int			i;

	*pipe = NULL;
	i = -1;
	upd = set->cmd;
	while (upd)
	{
		name_copy(upd, buffer, &i);
		if (!upd->next || !ms_strncmp(upd->next->name, "|", 1))
		{
			*(buffer + ++i) = '\0';
			i = -1;
			command_next_last(pipe, command_push(buffer));
			upd = upd->next;
			if (!upd)
				break ;
		}
		else
			*(buffer + ++i) = ' ';
		upd = upd->next;
	}	
}

static char	*command_move(t_command *cmd)
{
	char	*upd;

	upd = cmd->name;
	while (*upd && !has_space(*upd))
		upd++;
	while (*upd && has_space(*upd))
		upd++;
	return (upd);
}

void	pipe_argument_get(t_command *cmd, char ***arg)
{
	char	*upd;
	char	buffer[65535];
	int		i;
	int		j;

	j = pipe_argument_max(cmd);
	*arg = (char **)malloc((j + 2) * sizeof(char *));
	upd = command_move(cmd);
	*(*(arg + 0)) = ms_strdup("fucker");
	j = 0;
	while (*upd)
	{
		i = -1;
		while (*upd && !has_space(*upd))
			*(buffer + ++i) = *upd++;
		if (!*upd || has_space(*upd))
		{
			*(buffer + ++i) = '\0';
			*(*(arg + ++j)) = ms_strdup(buffer);
		}
		upd++;
	}
	*(*(arg + ++j)) = NULL;
}
