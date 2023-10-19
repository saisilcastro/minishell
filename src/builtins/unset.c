/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:48:08 by lumedeir          #+#    #+#             */
/*   Updated: 2023/10/19 12:41:11 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <variable.h>
#include <stdlib.h>
#include <minishell.h>
#include <stdio.h>

void	unset(t_variable **var, char *name)
{
	t_variable	*unset_var;
	int			i;

	i = 0;
	unset_var = *var;
	while (unset_var && !ms_strcmp(unset_var->name, name))
		unset_var = unset_var->next;
	while (unset_var->value[i])
		unset_var->value[i++] = '\0';
}
