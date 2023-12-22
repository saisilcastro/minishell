/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:23:18 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/21 17:11:38 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	t_minishell	*shell;

	shell = shell_get();
	shell_set(shell);
	shell_loop(shell);
	shell_pop(shell);
	return ((unsigned char)shell->status);
}
