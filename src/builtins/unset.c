/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:48:08 by lumedeir          #+#    #+#             */
/*   Updated: 2023/10/20 15:36:59 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset(t_variable **var, char *name)
{
	t_variable	*unset_var;
	int			index;

	index = 0;
	unset_var = *var;
	while (unset_var && !ms_strcmp(unset_var->name, name))
		unset_var = unset_var->next;
	if (unset_var && !ms_strcmp(unset_var->name, name))
		while (unset_var->value[index])
			unset_var->value[index++] = '\0';
	else
		printf("unset: command \"%s\" not found.\n", name);
}