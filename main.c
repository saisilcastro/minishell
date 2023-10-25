/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:23:18 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/24 15:49:52 by lumedeir         ###   ########.fr       */
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
