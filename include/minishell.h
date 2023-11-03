/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:24:46 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/02 20:24:36 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <variable.h>
# include <common.h>
# include <command.h>
# include <signal.h>
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define PURPLE "\033[1;35m"

typedef struct s_minishell	t_minishell;
struct s_minishell{
	t_variable	*var;
	t_command	*cmd;
};

extern void		shell_set(t_minishell *set);
extern void		shell_command(t_minishell *set);
extern void		shell_parse(t_minishell *set, char *command);
extern void		shell_loop(t_minishell *set);
extern void		shell_pop(t_minishell *set);

extern t_status	builtin_execute(t_minishell *set);
extern void		environment_push(t_minishell *set);
extern void		export_variable(t_variable **var, t_command *cmd);
extern void		expansion(t_command **list, t_variable *var);
extern void		node_delete(t_command **cmd, char *name);
//extern void		error(char *error, char **command, t_minishell *set);
extern void		command_parser(t_minishell *set, char *command);

extern void		export(t_variable **var, t_command *cmd);
extern void		cd(t_command *set);
extern void		pwd(void);
extern void		env(void);
extern void		unset(t_variable **var, t_command *cmd);
extern void		echo_execute(t_command *cmd);

#endif