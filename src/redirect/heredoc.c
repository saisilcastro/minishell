/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:05:45 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/05 16:32:42 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	heredoc(t_minishell *set, t_command *cmd, char *eof)
{
	char	*line;

	line = NULL;
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
}
