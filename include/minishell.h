/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumedeir < lumedeir@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:24:46 by lde-cast          #+#    #+#             */
/*   Updated: 2023/11/23 10:29:23 by lumedeir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
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
	t_command	*path;
	t_command	*file;
	t_status	run;
	void		(*redirect[4])(t_minishell *set);
	void		(*builtin[7])(t_minishell *set);
	short		status;
};

extern void			shell_set(t_minishell *set);
extern void			shell_function(t_minishell *set);
extern int			shell_index(t_minishell *set);
extern void			shell_path(t_minishell *set);
extern void			shell_command(t_minishell *set);
extern void			shell_parse(t_minishell *set, char *command);
extern t_status		shell_io(t_minishell *set);
extern void			shell_loop(t_minishell *set);
extern void			shell_pop(t_minishell *set);

extern void			shell_ctrl_c(int sig);
extern void			shell_ctrl_backslash(int sig);

extern void			environment_push(t_minishell *set);
extern void			export_variable(t_minishell *set);
extern void			expansion(t_command **list, t_variable *var, t_minishell *set);
extern void			node_delete(t_command **cmd, char *name);
extern t_status		command_parser(t_minishell *set, char *command);
extern t_status		quotes_is_closed(char *command, char c,
						t_minishell *set, t_status msg);
extern void			error(char *error);
extern void			error_and_clear(t_minishell *set, char *error);
extern void			remove_quotes(t_command *list, t_minishell *set);
extern int			upd_index(char *command, char c);
extern void			find_var(t_command *line, t_variable *var, int index,
						t_minishell *set);
extern int			arr_size(t_command *cmd);
extern int			count_args(t_command *cmd, char *redirect);

extern void			shell_redirect_minor(t_minishell *set);
extern void			shell_redirect_double_minor(t_minishell *set);
extern void			shell_redirect_major(t_minishell *set);
extern void			shell_redirect_double_major(t_minishell *set);
extern t_status		search_path(t_command *env, t_command *app, char *path);
extern t_command	*redirect_find(t_command *cmd, char *redirect);
extern void			argument_get(t_command *last, char ***arg, char *redirect);
extern void			symbol_remaider(char *command, char *buffer, int *i, char c);
extern int			handle_quotes(char *command, char *buffer, t_minishell *set);

extern void			echo(t_minishell *set);
extern void			export(t_minishell *set);
extern void			cd(t_minishell *set);
extern void			pwd(t_minishell *set);
extern void			env(t_minishell *set);
extern void			unset(t_minishell *set);
extern void			echo_execute(t_minishell *set);
extern void			exit_fn(t_minishell *set);

#endif