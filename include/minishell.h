/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:24:46 by lde-cast          #+#    #+#             */
/*   Updated: 2024/01/09 14:03:04 by lde-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <common.h>
# include <variable.h>
# include <command.h>
# include <signal.h>
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define PURPLE "\033[1;35m"

typedef struct s_pid		t_pid;
struct s_pid
{
	int			id;
	t_pid		*next;
};

extern t_pid		*pid_push(int id);
extern void			pid_next_first(t_pid **list, t_pid *pid);
extern void			pid_next_last(t_pid **list, t_pid *set);
extern t_pid		*pid_last(t_pid *list);
extern void			pid_pop(t_pid **list);

typedef struct s_minishell	t_minishell;
struct s_minishell
{
	t_variable	*var;
	t_command	*cmd;
	t_command	*path;
	t_command	*pipe;
	t_status	run;
	t_status	run_hdoc;
	t_status	flag;
	t_status	last_pipe;
	t_pid		*pid;
	char		*name;
	char		*hdoc;
	char		*home;
	int			fd_in;
	int			fd_out;
	int			fd_in_p;
	int			fd_out_p;
	void		(*special[2])(t_minishell *set, t_command *cmd);
	void		(*builtin[7])(t_minishell *set, t_command *cmd, int fd);
	int			status;
};

//                    shell
extern void			shell_set(t_minishell *set);
extern t_minishell	*shell_get(void);
extern void			shel_change(t_minishell *set);
extern void			shell_function(t_minishell *set);
extern int			shell_index(t_minishell *set, t_command **cmd, t_status p);
extern void			shell_path(t_minishell *set);
extern void			shell_path_update(t_minishell *set, char *path);
extern void			shell_command(t_minishell *set);
extern void			shell_parse(t_minishell *set, char *command);
extern void			shell_loop(t_minishell *set);
extern void			shell_pop(t_minishell *set);
extern void			shell_run(t_minishell *set);

//                    signal
extern void			shell_ctrl_c(int sig);
extern void			shell_execute_ctrl_c(int signal);
extern void			shell_ctrl_backslash(int sig);
extern void			heredoc_ctrl_c(int signal);
extern int			ft_check_if_signaled(void);

//                   parser and expansion
extern void			environment_push(t_minishell *set);
extern void			export_variable(t_minishell *set, t_command *cmd);
extern void			expansion(t_command **list, t_variable *v, t_minishell *s);
extern void			remove_quotes(t_command *list);
extern void			symbol_remaider(char *cmd, char *buffer, int *i, char c);
extern void			find_variable(t_command *line, t_variable *var, int index,
						t_minishell *set);
extern int			handle_quotes(char *cmd, char *buffer, t_minishell *set);
extern t_status		valid_name(char *name, char *value, t_minishell *set);
extern t_status		command_parser(t_minishell *set, char *command);
extern t_status		quotes_is_closed(char *command, char c,
						t_minishell *set, t_status msg);

//                     execute
extern void			argument_get(t_command *cmd, char ***arg);
extern void			redirect_argument_get(t_command *l, char ***arg);
extern void			builtin_execute(t_minishell *set, t_command *cmd,
						int builtin, char *name_cmd);
extern t_status		search_path(t_command *env, t_command *app, char *path);
extern t_command	*has_command(t_command *cmd);

//                     utils
extern void			ms_memset(void *mem, char c, int size);
extern void			free_arr(char **arg);
extern char			*get_name(char *line);
extern void			error_and_clear(t_minishell *set, char *error);
extern int			upd_index(char *command, char c);
extern int			count_args(t_command *cmd);
extern void			error(char *error, char *str, int fd);
extern void			node_delete(t_command **cmd, char *name);
extern void			print_buffer(int fd);

//						pipe functions

extern void			shell_pipe(t_minishell *set, t_command *cmd);
extern t_status		pipe_begin(t_minishell *set);
extern t_status		pipe_between(t_minishell *set);
extern t_status		pipe_end(t_minishell *set);

//                     handle files
extern t_status		close_fds(t_minishell *set);
extern t_status		open_fds(t_minishell *set, char *redirect, char *name);
extern t_status		get_infile(t_minishell *set, t_command *cmd);
extern void			fd_reset(t_minishell *set);

//                     redirects
extern void			shell_redirect(t_minishell *set, t_command *cmd);
extern void			heredoc(t_minishell *set, char *eof);
extern int			count_redirects(t_command *cmd, char *redirect);
extern t_status		has_redirect(t_command *cmd);
extern t_status		valid_redirect(t_command *cmd);
extern t_status		heredoc_is_last(t_command *cmd);
extern t_status		open_redirects(t_minishell *set, t_command *cmd);

//                      builtins
extern void			echo(t_minishell *set, t_command *cmd, int fd);
extern void			export(t_minishell *set, t_command *cmd, int fd);
extern void			cd(t_minishell *set, t_command *cmd, int fd);
extern void			pwd(t_minishell *set, t_command *cmd, int fd);
extern void			env(t_minishell *set, t_command *cmd, int fd);
extern void			unset(t_minishell *set, t_command *cmd, int fd);
extern void			echo_execute(t_minishell *set, t_command *cmd, int fd);
extern void			exit_fn(t_minishell *set, t_command *cmd, int fd);

#endif