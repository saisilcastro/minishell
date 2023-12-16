/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:27:20 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/15 19:47:14 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_args(t_command *cmd)
{
	t_command	*curr;
	int			count;

	curr = cmd;
	count = 0;
	while (curr)
	{
		if (has_redirect(curr))
		{
			curr = curr->next->next;
			while (curr && !has_redirect(curr))
			{
				count++;
				curr = curr->next;
			}	
		}
		else if (curr)
		{
			curr = curr->next;
			count++;
		}
	}
	return (count);
}

t_command	*has_command(t_command *cmd)
{
	t_command	*curr;

	if (!has_redirect(cmd))
		return (cmd);
	curr = cmd;
	while (curr)
	{
		if (has_redirect(curr))
		{
			curr = curr->next->next;
			if (!has_redirect(curr))
				return (curr);
		}
		else
			curr = curr->next;
	}
	return (NULL);
}

void	free_arr(char **arg)
{
	int	index;

	if (!arg || !*arg)
		return ;
	index = -1;
	while (arg[++index])
		free(arg[index]);
	free(arg);
}
