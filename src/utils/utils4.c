/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:27:20 by lumedeir          #+#    #+#             */
/*   Updated: 2023/12/22 12:56:24 by lde-cast         ###   ########.fr       */
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

static t_status	valid_first_char(t_minishell *set, char *name)
{
	if (ms_isalpha(name[0]) == Off && name[0] != '_')
	{
		if (name[0] == '-')
		{
			error(": invalid option", name, 2);
			set->status = 2;
		}
		else
		{
			error(": not a valid identifier", name, 2);
			set->status = 1;
		}
		return (Off);
	}
	return (On);
}

t_status	valid_name(char *name, char *value, t_minishell *set)
{
	int	index;

	index = 0;
	if (!valid_first_char(set, name))
		return (Off);
	while (name && name[++index])
	{
		if (ms_isdigit(name[index]) == Off && ms_isalpha(name[index]) == Off
			&& name[index] != '_')
		{
			error(": not a valid identifier", name, 2);
			set->status = 1;
			return (Off);
		}
	}
	if (!ms_strncmp(name, "PATH", 4))
		shell_path_update(set, value);
	return (On);
}
