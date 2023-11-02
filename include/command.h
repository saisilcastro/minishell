/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 12:47:56 by mister-code       #+#    #+#             */
/*   Updated: 2023/11/02 17:24:46 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <minishell.h>

typedef struct s_command	t_command;
struct s_command
{
	char		*name;
	t_command	*next;
};

extern t_command	*command_push(char *name);
extern void			command_next_last(t_command **list, t_command *set);
extern void			command_pop(t_command **list);

#endif