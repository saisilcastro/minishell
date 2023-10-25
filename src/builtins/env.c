/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:17:29 by lumedeir          #+#    #+#             */
/*   Updated: 2023/10/25 16:18:35 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	env(void)
{
	extern char	**__environ;

	while (*__environ)
	{
		printf("%s\n", *__environ);
		__environ++;
	}
}
