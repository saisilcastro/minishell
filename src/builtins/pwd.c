/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:54:28 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/23 19:29:50 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd(t_minishell *set, t_command *cmd)
{
	(void)set;
	(void)cmd;
	printf("%s\n", getcwd(NULL, 0));
	set->status = 0;
}
