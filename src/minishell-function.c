/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell-function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:36:51 by lde-cast          #+#    #+#             */
/*   Updated: 2023/12/05 11:20:12 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shell_function(t_minishell *set)
{
	set->redirect = shell_redirect;
	set->builtin[0] = echo_execute;
	set->builtin[1] = cd;
	set->builtin[2] = pwd;
	set->builtin[3] = export;
	set->builtin[4] = unset;
	set->builtin[5] = env;
	set->builtin[6] = exit_fn;
}
