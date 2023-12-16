/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:36:51 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/14 15:08:19 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_function(t_minishell *set)
{
	set->special[0] = shell_redirect;
	set->special[1] = shell_pipe;
	set->builtin[0] = echo_execute;
	set->builtin[1] = cd;
	set->builtin[2] = pwd;
	set->builtin[3] = export;
	set->builtin[4] = unset;
	set->builtin[5] = env;
	set->builtin[6] = exit_fn;
}
