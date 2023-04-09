# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 14:11:12 by amalbrei          #+#    #+#              #
#    Updated: 2023/04/09 12:57:03 by amalbrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEFAULT			=	\033[0m
RED				=	\033[1;31m
GREEN			=	\033[1;32m
YELLOW			=	\033[1;33m
PURPLE			=	\033[0;35m
CYAN			=	\033[1;36m

NAME			=	minishell
SUB_NAME		=	mini.a
SUB_LIB			=	libft/libft.a
OBJ_DIR			=	object_files
BUILTINS_DIR	=	builtins
ENVIRONMENT_DIR	=	environment
EXECUTION_DIR	=	execution
PARSING_DIR		=	parsing
SIGNALS_DIR		=	signals
MAIN_DIR		=	source_files
INC_DIR 		=	-I/usr/local/include -I/usr/local/opt/readline/include -Iincludes -Ilibft/includes
LIB				=	ar	-rcs
LIBFT			=	-Llibft -lft

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -g -fsanitize=address
MINI_FLAGS 		=	-L/usr/local/lib -L/usr/local/opt/readline/lib -lreadline 
RM				=	rm	-rf

BUILTINS_SRC 	=	msh_a_allocate.c msh_cd.c	msh_echo.c	msh_env.c	msh_exit.c	\
					msh_export.c	msh_pwd.c	msh_unset.c

ENVIRONMENT_SRC	=	msh_change.c	msh_create.c	msh_find.c	msh_ex.c

EXECUTION_SRC	=	msh_a_check.c	msh_execute.c	msh_here_doc.c	msh_locate.c	\
					msh_pipes.c		msh_pipex_split.c	msh_redirect.c

PARSING_SRC		=	constructor.c	env_handler1.c	env_handler2.c	final_command_builder1.c\
					parser1.c		parsing2.c		transfer_structs.c

SIGNALS_SRC		=	signals.c

MAIN_SRC 		=	minishell.c	msh_error.c	msh_free.c

SRC				=	$(BUILTINS_SRC) $(EXECUTION_SRC) $(PARSING_SRC) $(SIGNALS_SRC) $(ENVIRONMENT_SRC) $(MAIN_SRC)

OBJ				= 	$(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

all: $(SUB_LIB) $(NAME)  

$(SUB_LIB):
	@make libft.a -C libft
	@make bonus -C libft
	@make printf -C libft
	@make gnl -C libft

$(OBJ_DIR)/%.o: $(BUILTINS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "\033[A\033[2K\r$(GREEN)Compiling:"
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(ENVIRONMENT_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "\033[A\033[2K\r$(GREEN)Compiling:"
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(EXECUTION_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "\033[A\033[2K\r$(GREEN)Compiling:"
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARSING_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "\033[A\033[2K\r$(GREEN)Compiling:"
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(SIGNALS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "\033[A\033[2K\r$(GREEN)Compiling:"
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(MAIN_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "\033[A\033[2K\r$(GREEN)Compiling:"
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INC_DIR) $(OBJ) $(LIBFT) $(MINI_FLAGS) -o $(NAME)
	@printf "$(CYAN)\n==========================\n"
	@printf "$(CYAN) MINISHELL COMPILED\n"
	@printf "$(CYAN)==========================\n$(DEFAULT)"

norm:
	@norminette | grep Error

list:
	@make list -C libft

clean:
	@make clean -C libft
	@$(RM) $(OBJ_DIR)
	@printf "$(RED)CLEANING MSH.O FILES\n"

fclean: clean
	@make fclean -C libft
	@$(RM) $(NAME)
	@printf "$(RED)CLEANING MINISHELL PROGRAM\n"

re: fclean all

.PHONY = all $(NAME) $(LIBFT) norm list clean fclean re