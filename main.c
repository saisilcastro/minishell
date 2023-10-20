/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:23:18 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/20 11:28:14 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_variable	*var = NULL;
	t_variable	*upd;

	export(argc, argv, &var);
	upd = var;
	printf("%s %s\n", upd->next->name, upd->next->value);
	printf("%s %s\n", upd->name, upd->value);
	// upd = var;
	// unset(&var, "test1");
	return (0);
}
