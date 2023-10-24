/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:23:18 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/23 15:02:30 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>

int	main(void)
{
	t_minishell	hell;

	shell_set(&hell);
	shell_loop(&hell);
	shell_pop(&hell);
	return (0);
}
