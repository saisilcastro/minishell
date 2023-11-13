/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:23:18 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/13 17:05:40 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

typedef enum{
	
	APOSTROPHE = 239,
	DOUBLE_QUOTE = 249
}SPECIAL;

int	main(void)
{
	unsigned char	mine = 249;
	//t_minishell	hell;

	//shell_set(&hell);
	//shell_loop(&hell);
	//shell_pop(&hell);
	//return ((unsigned char)hell.status);
	if (mine == 249)
		printf("apostrofo\n");
	return (0);
}
