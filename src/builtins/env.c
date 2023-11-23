/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:17:29 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/23 19:23:48 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	env(t_minishell *set, t_command *cmd)
{
	extern char	**__environ;
	int			i;

	(void)cmd;
	i = -1;
	while (*(__environ + ++i))
		printf("%s\n", *(__environ + i));
	set->status = 0;
}
