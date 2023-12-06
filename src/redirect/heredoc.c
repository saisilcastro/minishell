/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:05:45 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/06 15:37:05 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_variable	*find_variable(t_minishell *set, char *line)
{
	t_variable	*curr;
	t_variable	*temp;

	curr = set->var;
	temp = NULL;
	while (curr)
	{
		if (!ms_name_cmp(line, curr->name, ms_strlen(curr->name)))
		{
			if (!temp)
				temp = curr;
			if (ms_strlen(curr->name) > ms_strlen(temp->name))
				temp = curr;
		}
		curr = curr->next;
	}
	if (temp)
		return (temp);
	return (NULL);
}

static char	*update_value(char *line, char *name, char *value)
{
	char	buffer[8000000];
	int		index;
	int		index2;

	index = -1;
	if (!line || !name)
		return (NULL);
	while (line && line[++index] != '$')
		buffer[index] = line[index];
	index2 = index + ms_strlen(name);
	while (value && *value)
	{
		buffer[index] = *value++;
		index++;
	}
	while (line && line[index2])
	{
		buffer[index] = line[index2++];
		index2++;
	}
	buffer[index] = '\0';
	free(line);
	return (ms_strdup(buffer));
}

static void	heredoc_expansion(t_minishell *set, char *line)
{
	int			index;
	t_variable	*curr;

	index = 0;
	while (line && line[index])
	{
		while (line[index] && line[index] != '$')
			index++;
		if (line[index] == '$' && find_variable(set, line + index + 1))
		{
			curr = find_variable(set, line + index + 1);
			line = update_value(line, curr->name, curr->value);
			index = 0;
			break ;
		}
		index++;
	}
}

void	heredoc(t_minishell *set, t_command *cmd, char *eof)
{
	char	*line;
	int		fd[2];

	line = NULL;
	if (pipe(fd) == -1)
		return ;
	while (1)
	{	
		line = readline("> ");
		if (line && !ms_strncmp(line, eof, ms_strlen(eof)))
		{
			free(line);
			break ;
		}
		add_history(line);
		if (line && ms_strchr(line, '$'))
			heredoc_expansion(set, line);
		ms_putstr_fd(line, fd[1]);
		ms_putstr_fd("\n", fd[1]);
		if (line && *line)
			free(line);
	}
	close(fd[1]);
	set->fd_in = fd[0];
}
