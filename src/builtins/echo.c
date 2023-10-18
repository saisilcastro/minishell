/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:06:24 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/18 13:23:45 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	echo(t_minishell *set, t_status newline)
{
	t_variable	*var;

	var = set->var;
	while (var)
	{
		if (var->active)
			printf("%s", var->value);
		var = var->next;
	}
	if (newline)
		putchar('\n');
}
echo $three $four;