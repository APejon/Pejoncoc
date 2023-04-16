/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:23:14 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/07 21:56:34 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_direct	**redir_content_init(t_direct **redir, int no_of_redir, int *avi,
char **av)
{
	int			k;

	k = -1;
	*avi = *avi + 1;
	while (++k < no_of_redir)
	{
		redir[k] = malloc(sizeof(t_direct));
		if (k == 0)
			redir[k]->direct = RE_OUTPUT;
		else if (k == 1)
			redir[k]->direct = HERE_DOC;
		if (redir[k]->direct == HERE_DOC)
			redir[k]->file = ft_strjoin(av[*avi], "\n");
		else
			redir[k]->file = ft_strdup(av[*avi]);
		redir[k]->hd_content = NULL;
		*avi = *avi + 2;
	}
	redir[k] = NULL;
	return (redir);
}

t_direct	**redir_init(int no_of_redir, int *avi, char **av)
{
	t_direct	**redir;

	if (no_of_redir == 0)
		return (NULL);
	else
		redir = malloc(sizeof(t_direct *) * (no_of_redir + 1));
	redir = redir_content_init(redir, no_of_redir, avi, av);
	return (redir);
}

char	**command_args_init(int no_of_cmd_args, int *avi, char **av)
{
	int		j;
	char	**args;

	j = -1;
	args = malloc(sizeof(char *) * (no_of_cmd_args + 1));
	while (++j < no_of_cmd_args)
	{
		args[j] = ft_strdup(av[*avi]);
		*avi = *avi + 1;
	}
	args[j] = NULL;
	return (args);
}

void	commands_init(t_shell *shell, int no_of_commands)
{
	int			i;

	shell->command = malloc(sizeof(t_command *) * (no_of_commands + 1));
	i = -1;
	while (++i < no_of_commands)
		shell->command[i] = malloc(sizeof(t_command));
	shell->command[i] = NULL;
}

void	shell_init(t_shell *shell)
{
	shell->exit_code = 0;
	shell->nohd = 0;
	shell->line = NULL;
	shell->oldpwd = NULL;
}

int	main(int ac, char **av, char **env)
{
	int		no_of_commands;
	int		no_of_cmd_args[1];
	int		no_of_redir[1];
	int		avi;
	int		i;
	int		exit;
	t_shell	*shell;
	t_env		*first;
	char		*oldpwd;

	(void)ac;
	shell = malloc(sizeof(t_shell));
	no_of_commands = 1;
	no_of_cmd_args[0] = 3;
	// no_of_cmd_args[1] = 2;
	// no_of_cmd_args[2] = 2;
	no_of_redir[0] = 0;
	// no_of_redir[1] = 0;
	// no_of_redir[2] = 0;
	shell_init(shell);
	commands_init(shell, no_of_commands);
	avi = 1;
	i = -1;
	while (++i < no_of_commands)
	{
		shell->command[i]->cmd_args = command_args_init(no_of_cmd_args[i],
				&avi, av);
		shell->command[i]->fd_in = STDIN_FILENO;
		shell->command[i]->fd_out = STDOUT_FILENO;
		shell->command[i]->p_fd[0] = STDIN_FILENO;
		shell->command[i]->p_fd[1] = STDOUT_FILENO;
		shell->command[i]->pid = 0;
		shell->command[i]->redir = redir_init(no_of_redir[i], &avi, av);
		avi++;
	}
	oldpwd = getcwd(NULL, 0);
	printf("o_pwd %s\n", oldpwd);
	msh_free(&oldpwd);
	msh_create_env(&shell, env);
	msh_create_denv(&shell, env);
	printf("BEFORE===========\n");
	first = shell->env;
	while (shell->env)
	{
		printf("ENV %s%s\n", shell->env->variable, shell->env->value);
		shell->env = shell->env->next;
	}
	shell->env = first;
	first = shell->dec_env;
	while (shell->dec_env)
	{
		printf("D_E %s%s\n", shell->dec_env->variable, shell->dec_env->value);
		shell->dec_env = shell->dec_env->next;
	}
	shell->dec_env = first;
	msh_command_dispenser(shell);
	oldpwd = getcwd(NULL, 0);
	printf("o_pwd %s\n", oldpwd);
	printf("AFTER===========\n");
	first = shell->env;
	while (shell->env)
	{
		printf("ENV %s%s\n", shell->env->variable, shell->env->value);
		shell->env = shell->env->next;
	}
	shell->env = first;
	first = shell->dec_env;
	while (shell->dec_env)
	{
		printf("D_E %s%s\n", shell->dec_env->variable, shell->dec_env->value);
		shell->dec_env = shell->dec_env->next;
	}
	shell->dec_env = first;
	exit = shell->exit_code;
	msh_complete_free(shell);
	msh_free(&oldpwd);
	return (exit);
}
