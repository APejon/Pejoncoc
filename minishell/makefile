# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 14:11:12 by amalbrei          #+#    #+#              #
#    Updated: 2023/01/29 15:20:46 by amalbrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEFAULT			=	\033[0m
RED				=	\033[1;31m
GREEN			=	\033[1;32m
YELLOW			=	\033[1;33m
PURPLE			=	\033[0;35m
CYAN			=	\033[1;36m

NAME			=	minishell
MAIN_DIR		=	source_files
BUILTINS_DIR	=	builtins
PARSING_DIR		=	parsing
EXECUTION_DIR	=	execution
OBJ_DIR			=	object_files
INC_DIR 		=	-Iincludes -Ilibft/includes
LIBFT			=	libft/libft.a

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror 
MINI_FLAGS 		=	-I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -lreadline 
RM				=	rm	-rf

BUILTINS_SRC 	=	msh_a_allocate.c msh_cd.c	msh_echo.c	msh_env.c	msh_exit.c	\
					msh_export.c	msh_pwd.c	msh_unset.c
BUILTINS_SRC 	:=	$(addprefix builtins/, $(BUILTINS_SRC))

ENVIRONMENT_SRC	=	msh_change.c	msh_create.c	msh_find.c
ENVIRONMENT_SRC	:=	$(addprefix environment/, $(ENVIRONMENT_SRC))

EXECUTION_SRC	=	msh_a_check.c	msh_execute.c	msh_here_doc.c	msh_locate.c	\
					msh_pipes.c		msh_pipex_split.c	msh_redirect.c
EXECUTION_SRC	:=	$(addprefix execution/, $(EXECUTION_SRC))

PARSING_SRC		=
PARSING_SRC		:=	$(addprefix parsing/, $(PARSING_SRC))

SIGNALS_SRC		=
SIGNALS_SRC		:=	$(addprefix signals/, $(SIGNALS_SRC))

MAIN_SRC 		=	msh_error.c		msh_free.c
MAIN_SRC 		:=	$(addprefix source_files/, $(MAIN_SRC))

SRC				=	$(BUILTINS_SRC) $(EXECUTION_SRC) $(PARSING_SRC) $(SIGNALS_SRC) $(ENVIRONMENT_SRC) $(MAIN_SRC)
OBJ				= 	$(SRC:%c=%o)

all: $(LIBFT) $(NAME)

$(BUILTINS_DIR)/%.o: $(BUILTINS_SRC)/%.c
	@mkdir -p $(BULTINS_DIR)
	@printf "\033[A\033[2K\r$(GREEN)Compiling:"
	$(CC) $(CFLAGS) $(INC_DIR) $(MINI_FLAGS) $(LIBFT) -c $< -o $@

$(ENVIRONMENT_DIR)/%.o: $(ENVIRONMENT_SRC)/%.c
	@mkdir -p $(ENVIRONMENT_DIR)
	@printf "\033[A\033[2K\r$(GREEN)Compiling:"
	$(CC) $(CFLAGS) $(INC_DIR) $(MINI_FLAGS) $(LIBFT) -c $< -o $@

$(EXECUTION_DIR)/%.o: $(EXECUTION_SRC)/%.c
	@mkdir -p $(EXECUTION_DIR)
	@printf "\033[A\033[2K\r$(GREEN)Compiling:"
	$(CC) $(CFLAGS) $(INC_DIR) $(MINI_FLAGS) $(LIBFT) -c $< -o $@
	
$(PARSING_DIR)/%.o: $(PARSING_SRC)/%.c
	@mkdir -p $(PARSING_DIR)
	@printf "\033[A\033[2K\r$(GREEN)Compiling:"
	$(CC) $(CFLAGS) $(INC_DIR) $(MINI_FLAGS) $(LIBFT) -c $< -o $@

$(SIGNALS_DIR)/%.o: $(SIGNALS_SRC)/%.c
	@mkdir -p $(SIGNALS_DIR)
	@printf "\033[A\033[2K\r$(GREEN)Compiling:"
	$(CC) $(CFLAGS) $(INC_DIR) $(MINI_FLAGS) $(LIBFT) -c $< -o $@

$(MAIN_DIR)/%.o: $(MAIN_SRC)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "\033[A\033[2K\r$(GREEN)Compiling:"
	$(CC) $(CFLAGS) $(INC_DIR) $(MINI_FLAGS) $(LIBFT) -c $< -o $@


$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INC_DIR) $(MINI_FLAGS) $(LIBFT) $(OBJ) -o $(NAME)
	@printf "$(CYAN)\n==========================\n"
	@printf "$(CYAN) SIMULATION READY\n"
	@printf "$(CYAN)==========================\n"

$(LIBFT):
	@make libft.a -C libft
	@make printf -C libft

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