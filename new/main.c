#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <string.h>

typedef struct s_minishell	t_minishell;
struct s_minishell{
	void	(*builtin[7])(char *name);
	void	(*redirect[4])(char *name);
};

void	echo(char *name)
{
	printf("inside echo %s\n", name);
}

void	cd(char *name)
{
	printf("inside cd %s\n", name);
}

void	pwd(char *name)
{
	printf("inside pwd %s\n", name);
}

void	export(char *name)
{
	printf("inside export %s\n", name);
}

void	unset(char *name)
{
	printf("inside unset %s\n", name);
}

void	env(char *name)
{
	printf("inside env %s\n", name);
}

void	exit_fn(char *name)
{
	printf("inside exit %s\n", name);
	exit(0);
}

void minor(char *name)
{
	printf("inside < %s\n", name);
}

void adult(char *name)
{
	printf("inside > %s\n", name);
}

void double_minor(char *name)
{
	printf("inside << %s\n", name);
}

void double_adult(char *name)
{
	printf("inside >> %s\n", name);
}

void shell_function(t_minishell *set)
{
	set->builtin[0] = echo;
	set->builtin[1] = cd;
	set->builtin[2] = pwd;
	set->builtin[3] = export;
	set->builtin[4] = unset;
	set->builtin[5] = env;
	set->builtin[6] = exit_fn;
	set->redirect[0] = minor;
	set->redirect[1] = adult;
	set->redirect[2] = double_minor;
	set->redirect[3] = double_adult;
}

int	get_index(char *cmd)
{
	if (!strncmp(cmd, "echo", 4))
		return (0);
	if (!strncmp(cmd, "cd", 2))
		return (1);
	if (!strncmp(cmd, "pwd", 3))
		return (2);
	if (!strncmp(cmd, "export", 6))
		return (3);
	if (!strncmp(cmd, "unset", 5))
		return (4);
	if (!strncmp(cmd, "env", 3))
		return (5);
	if (!strncmp(cmd, "exit", 4))
		return (6);
	if (!strncmp(cmd, "<<", 2))
		return (9);
	if (!strncmp(cmd, ">>", 2))
		return (10);
	if (!strncmp(cmd, "<", 1))
		return (7);
	if (!strncmp(cmd, ">", 1))
		return (8);
	return (-1);
}

int	main(void)
{
	t_minishell	hell;
	int			i;
	char		*command;

	shell_function(&hell);
	while (1)
	{
		command = readline("-minishell: ");
		i = get_index(command);
		printf("%i\n", i);
		if (i >= 0 && i < 7)
		{
			printf("here\n");
			hell.builtin[i]("fucker");
		}
		else if (i > 6)
		{
			printf("there\n");
			hell.redirect[i - 7]("sucker");
		}
		free(command);
	}
	return (0);
}
