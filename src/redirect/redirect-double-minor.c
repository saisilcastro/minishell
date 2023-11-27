/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-double-minor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:05:45 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/27 15:50:23 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	write_line(char *line)
{
	ms_putstr_fd("> ", 1);
	ms_putstr_fd(line, 1);
	ms_putstr_fd("\n", 1);
}

void	shell_redirect_double_minor(t_minishell *set)
{
	char	*line;
	char	*eof;

	line = NULL;
	eof = redirect_file(set->cmd, "<<")->name;
	while (1)
	{	
		line = readline("> ");
		if (line && !ms_strncmp(line, eof, ms_strlen(eof)))
		{
			free(line);
			break ;
		}
		add_history(line);
		if (line && *line)
			free(line);
	}
	return ;
}
