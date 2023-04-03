/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 02:22:39 by yhaidar           #+#    #+#             */
/*   Updated: 2023/04/03 10:23:37 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Initialises All Data */
t_shell	*initialiser(char **envp)
{
	t_shell	*data;

	(void)envp;
	data = ft_calloc(1, sizeof(t_shell));
	data->par = ft_calloc(1, sizeof(t_parser));
	data->exit_code = 0;
	data->nohd = 0;
	data->line = NULL;
	data->oldpwd = NULL;
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_shell		*data;

	(void)argc;
	(void)argv;
	data = initialiser(env);
	msh_create_env(&data, env);
	msh_create_denv(&data, env);
	signal(SIGINT, signal_handler_parent);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		data->lexar = NULL;
		data->line = readline("minishell:> ");
		if (data->line == NULL)
			break ;
		if (ft_strncmp(data->line, "\n", 3))
			continue ;
		add_history(data->line);
		if (parser(data, &data->line))
			msh_command_dispenser(data);
		if (data->line)
			free(data->line);
	}
	msh_free_to_exit(data);
}