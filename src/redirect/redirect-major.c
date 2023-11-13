/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-major.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mister-coder <mister-coder@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:06:27 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/12 20:31:43 by mister-code      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void file_replacer(t_minishell *set)
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

static void	file_in_execute(t_minishell *set)
{
	t_command	*cmd;

	printf("[%s]\n", set->cmd->name);
	if (!set->cmd->next)
		return ;
	cmd = set->cmd->next->next->next;
	while (cmd)
	{
		printf("{%s}\n", cmd->name);
		cmd = cmd->next;
	}
	printf("executing those\n");
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
