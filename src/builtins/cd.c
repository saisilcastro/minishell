/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:06:43 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/22 11:13:00 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	update_oldpwd(t_variable **var, char *oldpwd)
{
	t_variable	*curr_var;

	curr_var = variable_search(*var, "OLDPWD");
	if (curr_var)
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
