/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:06:43 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/21 15:57:43 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	update_oldpwd(t_variable **var, char *oldpwd)
{
	t_variable	*curr_var;

	curr_var = *var;
	while (curr_var->name && !ms_strncmp(curr_var->name, "OLDPWD", 6))
		curr_var = curr_var->next;
	if (ms_strncmp(curr_var->name, "OLDPWD", 6))
	{
		free(curr_var->value);
		curr_var->value = ms_strdup(oldpwd);
	}
}

void	cd(t_minishell *set)
{
	char	*temp;

	if (set->cmd->next->next)
	{
		ms_putstr_fd("cd: too many arguments\n", 2);
		set->status = 1;
		return ;
	}
	temp = ms_strdup(getcwd(NULL, 0));
	if (chdir(set->cmd->next->name) != 0)
	{
		ms_putstr_fd("cd: No such file or directory\n", 2);
		set->status = 1;
		free(temp);
		return ;
	}
	update_oldpwd(&set->var, temp);
	set->status = 0;
	free(temp);
}
