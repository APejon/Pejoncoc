# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/06 14:11:12 by amalbrei          #+#    #+#              #
#    Updated: 2022/12/09 16:25:12 by amalbrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEFAULT	=	\033[0m
RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
PURPLE	=	\033[0;35m
CYAN	=	\033[1;36m

NAME	=	minishell
SRC_DIR	=	source_files
BLD_DIR	=	builtins
PAR_DIR	=	parsing
EXE_DIR	=	execution
OBJ_DIR	=	object_files
INC_DIR =	-Iincludes -Ilibft
LIBFT	=	libft/libft.a

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror 
MINI_FLAGS = -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -lreadline 
RM		=	rm	-rf

SRCS = 

SRC 	+=	
OBJ	= 	$(addprefix $(OBJ_DIR)/, $(SRC:%c=%o))

all: $(LIBFT) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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