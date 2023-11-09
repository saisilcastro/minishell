/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:22:39 by mister-code       #+#    #+#             */
/*   Updated: 2023/11/08 12:29:55 by lde-cast         ###   ########.fr       */
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

void	echo_execute(t_command *cmd)
{
	t_command	*upd;
	t_status	newline;
	char		space;

	newline = On;
	space = ' ';
	if (!cmd)
		return ;
	upd = cmd;
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
}
