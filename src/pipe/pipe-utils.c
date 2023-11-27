/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe-utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:04:49 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/27 14:37:58 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pipe_argument_max(t_command *pipe)
{
	int		max;
	char	*cmd;

	max = 0;
	cmd = pipe->name;
	while (cmd && *cmd)
	{
		if (has_space(*cmd))
		{
			max++;
			while (cmd && *cmd && has_space(*cmd))
				cmd++;
			if (!*cmd)
				break ;
		}
		cmd++;
	}
	return (max);
}
