/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:05:45 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/15 19:55:09 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_variable	*find_var(t_minishell *set, char *line)
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

static char	*upd_value(char **line, char *name, char *value)
{
	char	buffer[65535];
	int		i;
	int		index2;

	if (!*line || !name)
		return (NULL);
	i = -1;
	while (*line && *(*line + ++i) && *(*line + i) != '$')
		buffer[i] = *(*line + i);
	index2 = i + ms_strlen(name) + 1;
	while (value && *value)
	{
		buffer[i] = *value++;
		i++;
	}
	while (*line && *(*line + index2))
	{
		buffer[i] = *(*line + index2);
		i++;
		index2++;
	}
	buffer[i] = '\0';
	free(*line);
	return (ms_strdup(buffer));
}

static void	heredoc_expansion(t_minishell *set, char **line)
{
	int			index;
	char		*temp;

	index = 0;
	while (*line && *(*line + index))
	{
		while (*(*line + index) && *(*line + index) != '$')
			index++;
		if (*(*line + index) && *(*line + index) == '$' && *(*line + index + 1))
		{
			if (find_var(set, *line + index + 1))
				*line = upd_value(line, find_var(set, *line + index + 1)->name,
						find_var(set, *line + index + 1)->value);
			else if (*(*line + index) == '$' && *(*line + index + 1)
				&& !find_var(set, *line + index + 1))
			{
				temp = get_name(*line + index + 1);
				*line = upd_value(line, temp, NULL);
				free(temp);
			}
			index = 0;
		}
		if (*(*line + index))
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
			heredoc_expansion(set, &line);
		ms_putstr_fd(line, fd[1]);
		ms_putstr_fd("\n", fd[1]);
		if (line || !*line)
			free(line);
	}
	close(fd[1]);
	set->fd_in = fd[0];
}
