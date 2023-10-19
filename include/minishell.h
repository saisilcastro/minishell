/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:24:46 by lde-cast          #+#    #+#             */
/*   Updated: 2023/10/19 12:23:10 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <variable.h>
# include <builtins/echo.h>
# include <command.h>

typedef struct s_minishell	t_minishell;
struct s_minishell{
	t_variable	*var;
	t_command	*cmd;
};

extern void			shell_set(t_minishell *set);
extern void			shell_command(t_minishell *set);
extern void			shell_parse(t_minishell *set, char *command);
extern void			shell_pop(t_minishell *set);

extern void			export(int argc, char **argv, t_variable **var);
extern t_variable	*variable_node(char *string);

void				unset(t_variable **var, char *name);

#endif