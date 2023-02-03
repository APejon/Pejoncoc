/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:23:14 by amalbrei          #+#    #+#             */
/*   Updated: 2023/02/03 21:39:07 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	int			i;
	int			j;
	int			k;
	int			no_of_commands;
	t_shell		*shell;
	// t_env		*first;
	// char		*oldpwd;

	(void)ac;
	no_of_commands = 1;
	shell = malloc(sizeof(t_shell));
	shell->exit_code = 0;
	shell->nohd = 0;
	shell->current_line = NULL;
	shell->line = NULL;
	shell->oldpwd = NULL;
	shell->command = malloc(sizeof(t_command *) * (no_of_commands + 1));
	i = -1;
	while (++i < no_of_commands)
		shell->command[i] = malloc(sizeof(t_command));
	shell->command[i] = NULL;
	shell->command[0]->cmd_args = malloc(sizeof(char *) * 2);
	i = -1;
	j = 0;
	while (++i < 1)
		shell->command[j]->cmd_args[i] = ft_strdup(av[i + 1]);
	shell->command[j]->cmd_args[i] = NULL;
	shell->command[j]->redir = malloc(sizeof(t_direct *) * 2);
	i++;
	k = -1;
	while (++k < 1)
	{
		shell->command[j]->redir[k] = malloc(sizeof(t_direct));
		if (k == 0)
			shell->command[j]->redir[k]->direct = RE_INPUT;
		else if (k == 1)
			shell->command[j]->redir[k]->direct = RE_OUTPUT;
		shell->command[j]->redir[k]->file = ft_strdup(av[i + 1]);
		i = i + 2;
	}
	shell->command[j]->redir[k] = NULL;
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
	// msh_free(&oldpwd);
	return (0);
}
