/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:23:14 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/07 13:15:24 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell		*shell;
	t_command	*command;
	// t_env		*first;
	char		*value;
	// char		*oldpwd;

	(void)ac;
	shell = malloc(sizeof(t_shell));
	command = malloc(sizeof(t_command));
	command->command = av[1];
	command->flag =	NULL;
	if (av[2])
		value = ft_strdup(av[2]);
	else
		value = NULL;
	command->target = value;
	shell->command = command;
	printf("%s, %s and %s\n", shell->command->command, shell->command->flag, shell->command->target);
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
	msh_allocate(shell);
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
	msh_free_list(&shell->env);
	msh_free_list(&shell->dec_env);
	free(value);
	free(command);
	free(shell);
	// oldpwd = getcwd(NULL, 0);
	// printf("%s\n", oldpwd);
	// free (oldpwd);
	return (0);
}
