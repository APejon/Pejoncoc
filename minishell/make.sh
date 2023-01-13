make clean -C libft
make fclean -C libft
make -C libft
gcc -Werror -Wextra -Wall -Iincludes -Ilibft/includes source_files/msh_utils.c environment/msh_change_env.c environment/msh_create_env.c environment/msh_find.c builtins/msh_allocate.c builtins/msh_cd.c builtins/msh_echo.c builtins/msh_env.c builtins/msh_exit.c builtins/msh_export.c builtins/msh_pwd.c builtins/msh_unset.c main.c libft/libft.a -g3