/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:06:43 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/12 15:17:29 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	update_oldpwd(t_variable **var, char *oldpwd)
{
	t_variable	*curr_var;

	curr_var = var_search(*var, "OLDPWD");
	if (curr_var)
	{
		free(curr_var->value);
		curr_var->value = ms_strdup(oldpwd);
	}
}

void	cd(t_minishell *set, t_command *cmd, int fd)
{
	char	*temp;

	if (cmd->next->next)
	{
		ms_putstr_fd("cd: too many arguments\n", 2);
		set->status = 1;
		return ;
	}
	temp = ms_strdup(getcwd(NULL, 0));
	if (chdir(cmd->next->name) != 0)
	{
		ms_putstr_fd("cd: No such file or directory\n", 2);
		set->status = 1;
		free(temp);
		return ;
	}
	update_oldpwd(&set->var, temp);
	free(temp);
	set->status = 0;
}
