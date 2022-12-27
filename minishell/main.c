/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:23:14 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/27 17:58:41 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell		*shell;
	t_command	*command;
	// char		*oldpwd;
	int			i;
	int			j;
	int			k;

	(void)ac;
	i = 0;
	j = 0;
	k = 0;
	shell = malloc(sizeof(t_shell));
	command = malloc(sizeof(t_command));
	command->command = av[1];
	command->flag = av[2];
	command->target = av[3];
	shell->command = command;
	printf("%s, %s and %s\n", shell->command->command, shell->command->flag, shell->command->target);
	msh_create_env(shell, env);
	msh_create_denv(shell, env);
	// msh_export(shell, shell->command);
	msh_free_list(&shell->env);
	msh_free_list(&shell->dec_env);
	free(command);
	free(shell);
	// oldpwd = getcwd(NULL, 0);
	// printf("%s\n", oldpwd);
	return (0);
}
