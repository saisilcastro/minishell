# **************************************************************************** #
#     ALL CREDITS TO SHEELA E LUCAS KUN BY THE TESTER STRUCTURE, I JUST        #
#     MODIFIED A LITTLE BIT AND ORGANIZED TO SATISFY SOME SPECIFIC NEEDS       #
#     I HAD DURING MY PROJECT IMPLEMENTATION!                                  #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acapela- <acapela-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2023/08/04 14:56:35 by acapela-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#*****************************
#                            *
#    PHOENIXSHELL TESTER     *
#                            *
#*****************************
MINISHELL_PATH = ../
MINISHELL = ../minishell

all:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester

clean:
	@find . -maxdepth 1 -type f ! -name "Makefile" -delete
	rm -rfd phoenixpaste

1:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/1_simple_commands

2:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/2_arguments

3:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/3_echo

4:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/4_exit

5:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/5_exit_code

7:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/7_double_quotes

8:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/8_single_quotes

9:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/9_export

10:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/10_unset

11:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/11_cd

12:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/12_pwd

13:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/13_relative_path

14:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/14_environment_path

15:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/15_redirection

16:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/16_pipes

17:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/17_go_crazy

18:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/18_environment_variable

19:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/19_syntax

20:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@./srcs/tester ./srcs/tests/extra/20_mand

21:
	@make -C $(MINISHELL_PATH) --no-print-directory
	@bash ./srcs/tests/extra/21_welton.sh
