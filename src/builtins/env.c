/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:17:29 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/10 16:38:55 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	env(t_minishell *set)
{
	extern char	**__environ;
	int			i;

	(void)set;
	i = -1;
	while (*(__environ + ++i))
		printf("%s\n", *(__environ + i));
}
