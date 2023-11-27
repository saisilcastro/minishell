/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:48:32 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/27 15:39:29 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	argument_pop(char ***arg);

void	pipe_execute(t_minishell *set)
{
	t_command	*pipe;
	t_command	*upd;
	char		**arg;

	pipe_extract(set, &pipe);
	upd = pipe;
	while (upd)
	{
		pipe_argument_get(upd, &arg);
		upd = upd->next;
		argument_pop(&arg);
	}
	command_pop(&pipe);
}

static void	argument_pop(char ***arg)
{
	int		i;

	if (!*arg)
		return ;
	i = -1;
	while (*(*(arg + ++i)))
	{
		printf("###%s\n", *(*(arg + i)));
		free(*(*(arg + i)));
	}
	free(*arg);
}
