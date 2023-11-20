/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect-major.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 22:06:27 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/20 13:56:02 by lumedeir         ###   ########.fr       */
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

static void	file_in_execute(t_minishell *set)
{
	char		**execute;
	t_command	*cmd;
	int			i;

	if (!set->cmd->next)
		return ;
	i = 1;
	execute = (char **)malloc((command_size(set->cmd) - 1) * sizeof(char *));
	*(execute + 0) = ms_strdup(set->cmd->name);
	cmd = set->cmd->next->next->next;
	while (cmd)
	{
		*(execute + i++) = ms_strdup(cmd->name);
		printf("{%s}\n", cmd->name);
		cmd = cmd->next;
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
