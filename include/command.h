/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 12:47:56 by mister-code       #+#    #+#             */
/*   Updated: 2023/12/18 20:56:37 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <minishell.h>

typedef struct s_command	t_command;
struct s_command
{
	char		*name;
	t_status	flag_quotes;
	t_command	*next;
};

extern t_command	*command_push(char *name, t_status flag);
extern void			command_next_last(t_command **list, t_command *set);
extern int			command_size(t_command *list);
extern void			command_pop(t_command **list);
extern void			command_pop_first(t_command **head);
extern void			command_show(t_command *cmd, int fd);

#endif