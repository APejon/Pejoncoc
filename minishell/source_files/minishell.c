/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 02:22:39 by yhaidar           #+#    #+#             */
/*   Updated: 2023/04/08 20:00:43 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	msh_eof(t_shell *data)
{
	msh_free(&data->oldpwd);
	msh_free(&data->par);
	msh_free(&data);
	printf("exit\n");
}

void	msh_reset(t_shell *data)
{
	int	i;

	i = -1;
	ft_bzero(data->line, ft_strlen(data->line));
	msh_free(&data->line);
	data->nohd = 0;
	// while (data->command[++i])
	// 	msh_array_free(data, i);
	// msh_free(&data->command);
}

/* Initialises All Data */
t_shell	*initialiser(char **env)
{
	t_shell	*data;

	data = ft_calloc(1, sizeof(t_shell));
	data->par = ft_calloc(1, sizeof(t_parser));
	data->exit_code = 0;
	data->nohd = 0;
	data->line = NULL;
	data->oldpwd = getcwd(NULL, 0);
	msh_create_env(&data, env);
	msh_create_denv(&data, env);
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_shell		*data;

	(void)argc;
	(void)argv;
	data = initialiser(env);
	signal(SIGINT, signal_handler_parent);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		data->line = ft_strtrim(readline("\033[1;33mminishell:B> \033[0m"),
				" \v\t\f\r\n");
		if (data->line == NULL)
			break ;
		if (data->line[0] == 0)
		{
			msh_free(&data->line);
			continue ;
		}
		add_history(data->line);
		if (parser(data, &data->line))
			msh_command_dispenser(data);
		msh_reset(data);
	}
	msh_eof(data);
}
