/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:36:51 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/10 21:59:11 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_function(t_minishell *set)
{
	set->redirect[0] = shell_redirect_double_minor;
	set->redirect[1] = shell_redirect_double_major;
	set->redirect[2] = shell_redirect_minor;
	set->redirect[3] = shell_redirect_major;
	set->builtin[0] = echo_execute;
	set->builtin[1] = cd;
	set->builtin[2] = pwd;
	set->builtin[3] = export;
	set->builtin[4] = unset;
	set->builtin[5] = env;
	set->builtin[6] = exit_fn;
}
