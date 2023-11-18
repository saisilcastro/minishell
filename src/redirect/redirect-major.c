/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-major.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:06:27 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/18 05:12:05 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	file_replacer(t_minishell *set)
{
	int	fd;

	fd = 0;
	if (access(set->cmd->next->name, F_OK) != -1)
		unlink(set->cmd->next->name);
	fd = open(set->cmd->next->name, O_WRONLY | O_CREAT, 00700);
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

	*arg = (char **)malloc((command_size(last) + 1) * sizeof(char *));
	if (!*arg)
		return ;
	i = 0;
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

	if (!set->cmd->next->next)
	{
		printf("syntax error near unexpected token `newline'\n");
		return ;
	}
	if (search_path(set->path, set->cmd, path))
	{
		fd = open(set->cmd->next->next->name, O_WRONLY | O_CREAT, 0777);
		argument_get(set->cmd->next->next->next, &arg);
		dup2(fd, STDOUT_FILENO);
		execve(path, arg, __environ);
		close(fd);
	}
}

void	shell_redirect_major(t_minishell *set)
{
	if (set->cmd->next)
	{
		if (!ms_strncmp(set->cmd->name, ">", 1))
			file_replacer(set);
		else if (!ms_strncmp(set->cmd->next->name, ">", 1))
			file_in_execute(set);
	}
}
