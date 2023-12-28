/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:05:45 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/28 15:57:02 by lde-cast         ###   ########.fr       */
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

static t_status	verify(char **line, char *eof)
{
	if (*line == NULL && shell_get()->status != 130)
	{
		ms_putstr_fd("minishell: warning: here-document at line 22 delimited "
			"by end-of-file (wanted `eof')\n", 2);
		return (Off);
	}
	if (*line && !ms_strncmp(*line, eof, ms_strlen(eof)))
	{
		free(*line);
		return (Off);
	}
	if (!*line && shell_get()->status == 130)
	{
		write(2, "\n", 1);
		return (Off);
	}
	if (*line && !**line)
		write(2, "\n", 1);
	return (On);
}

void	heredoc(t_minishell *set, char *eof)
{
	int		fd[2];
	int		fdin;

	if (pipe(fd) == -1)
		return ;
	set = shell_get();
	fdin = dup(STDIN_FILENO);
	while (set->run_hdoc)
	{
		signal(SIGINT, heredoc_ctrl_c);
		ms_putstr_fd("> ", 1);
		set->hdoc = readline("");
		if (!verify(&set->hdoc, eof) || !set->run_hdoc)
			break ;
		add_history(set->hdoc);
		if (set->hdoc && ms_strchr(set->hdoc, '$'))
			heredoc_expansion(set, &set->hdoc);
		ms_putstr_fd(set->hdoc, fd[1]);
		ms_putstr_fd("\n", fd[1]);
		if (set->hdoc || !*set->hdoc)
			free(set->hdoc);
	}
	dup2(fdin, STDIN_FILENO);
	close(fd[1]);
	set->fd_in = fd[0];
}
