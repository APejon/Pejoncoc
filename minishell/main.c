/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:23:14 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/29 18:14:44 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell		*shell;
	t_command	*command;
	// t_env		*first;
	// char		*oldpwd;

	(void)ac;
	shell = malloc(sizeof(t_shell));
	shell->command = malloc(sizeof(char *) * 1);
	command = malloc(sizeof(t_command));
	command->cmd_args = malloc(sizeof(char *) * ac - 1);
	command->cmd_args[0] = av[1];
	command->cmd_args[1] = av[2];
	command->cmd_args[2] = av[3];
	shell->command[0] = command;
	printf("%s, %s and %s\n", shell->command[0]->cmd_args[0], shell->command[0]->cmd_args[1], shell->command[0]->cmd_args[2]);
	// oldpwd = getcwd(NULL, 0);
	// printf("%s\n", oldpwd);
	// free (oldpwd);
	msh_create_env(&shell, env);
	msh_create_denv(&shell, env);
	// printf("BEFORE===========\n");
	// first = shell->env;
	// while (shell->env)
	// {
	// 	printf("%s%s\n", shell->env->variable, shell->env->value);
	// 	shell->env = shell->env->next;
	// }
	// shell->env = first;
	// first = shell->dec_env;
	// while (shell->dec_env)
	// {
	// 	printf("declare -x %s%s\n", shell->dec_env->variable, shell->dec_env->value);
	// 	shell->dec_env = shell->dec_env->next;
	// }
	// shell->dec_env = first;
	msh_command_dispenser(shell);
	// printf("AFTER===========\n");
	// first = shell->env;
	// while (shell->env)
	// {
	// 	printf("%s%s\n", shell->env->variable, shell->env->value);
	// 	shell->env = shell->env->next;
	// }
	// shell->env = first;
	// first = shell->dec_env;
	// while (shell->dec_env)
	// {
	// 	printf("declare -x %s%s\n", shell->dec_env->variable, shell->dec_env->value);
	// 	shell->dec_env = shell->dec_env->next;
	// }
	// shell->dec_env = first;
	msh_complete_free(shell);
	// oldpwd = getcwd(NULL, 0);
	// printf("%s\n", oldpwd);
	// free (oldpwd);
	return (0);
}
