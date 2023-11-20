/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-major.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:06:27 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/20 14:06:57 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	file_replacer(char *path)
{
	int	fd;

	fd = 0;
	if (access(path, F_OK) != -1)
		unlink(path);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 00700);
	lseek(fd, 0, SEEK_SET);
	write(fd, "\0", 1);
	close(fd);
}

static t_status	search_path(t_command *env, t_command *app, char *path)
{
	t_command	*upd;
	int			i;
	int			j;

	upd = env;
	while (upd)
	{
		i = -1;
		while (*(upd->name + ++i))
			*(path + i) = *(upd->name + i);
		*(path + i++) = '/';
		j = -1;
		while (*(app->name + ++j))
			*(path + i++) = *(app->name + j);
		*(path + i) = '\0';
		if (!access(path, F_OK))
			break ;
		else
			i = 0;
		upd = upd->next;
	}
	*(path + i) = '\0';
	return (i);
}

static void	argument_get(t_command *last, char ***arg)
{
	t_command	*upd;
	int			i;

	*arg = (char **)malloc((command_size(last) + 2) * sizeof(char *));
	if (!*arg)
		return ;
	*(*arg + 0) = ms_strdup("fucker");
	i = 1;
	upd = last;
	while (upd)
	{
		*(*arg + i) = ms_strdup(upd->name);
		upd = upd->next;
		i++;
	}
	*(*arg + i) = NULL;
}

static void	file_in_execute(t_minishell *set)
{
	char		path[4096];
	char		**arg;
	int			fd;
	int			pid;

	if (!set->cmd->next->next)
	{
		printf("syntax error near unexpected token `newline'\n");
		return ;
	}
	if (search_path(set->path, set->cmd, path))
	{
		pid = fork();
		if (pid == 0)
		{
			fd = open(set->cmd->next->next->name,
					O_WRONLY | O_CREAT | O_TRUNC, 0777);
			dup2(fd, STDOUT_FILENO);
			argument_get(set->cmd->next->next->next, &arg);
			execve(path, arg, __environ);
			close(fd);
		}
	}
}

void	shell_redirect_major(t_minishell *set)
{
	if (set->cmd->next)
	{
		if (!ms_strncmp(set->cmd->name, ">", 1))
			file_replacer(set->cmd->next->name);
		else if (!ms_strncmp(set->cmd->next->name, ">", 1))
			file_in_execute(set);
	}
}
