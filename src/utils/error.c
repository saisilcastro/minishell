/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:29:41 by lumedeir          #+#    #+#             */
/*   Updated: 2023/11/13 15:29:27 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_and_clear(t_minishell *set, char *error)
{
	ms_putstr_fd(PURPLE">minishell: " WHITE, 2);
	ms_putstr_fd(error, 2);
	write(2, "\n", 1);
	command_pop(&set->cmd);
}

void	error(char *error)
{
	ms_putstr_fd(PURPLE">minishell: " WHITE, 2);
	ms_putstr_fd(error, 2);
	write(2, "\n", 1);
}
