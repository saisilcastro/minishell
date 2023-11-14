/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:22:39 by mister-code       #+#    #+#             */
/*   Updated: 2023/11/14 16:30:18 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	skip_newline(t_command **cmd, t_status *newline)
{
	int	size;
	int	i;

	if (*cmd && !ms_strncmp((*cmd)->name, "-n", 2))
	{
		while (*cmd)
		{
			size = ms_strlen((*cmd)->name);
			i = 1;
			while (i < size)
			{
				if ((*cmd)->name[i] != 'n')
					return ;
				i++;
			}
			*newline = Off;
			*cmd = (*cmd)->next;
		}
	}
}

void	echo_execute(t_minishell *set)
{
	t_command	*upd;
	t_status	newline;
	char		space;

	newline = On;
	space = ' ';
	if (!set->cmd)
		return ;
	upd = set->cmd->next;
	skip_newline(&upd, &newline);
	while (upd)
	{	
		if (upd->next == NULL)
			space = '\0';
		printf("%s%c", upd->name, space);
		upd = upd->next;
	}
	if (newline)
		printf("\n");
	set->status = 0;
}
