/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:29:41 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/29 12:27:36 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_and_clear(t_minishell *set, char *error)
{
	ms_putstr_fd("minishell: " WHITE, 2);
	ms_putstr_fd(error, 2);
	write(2, "\n", 1);
	command_pop(&set->cmd);
}

void	error(char *error, char *str)
{
	ms_putstr_fd("minishell: " WHITE, 2);
	if (str)
		ms_putstr_fd(str, 2);
	ms_putstr_fd(error, 2);
	write(2, "\n", 1);
}
