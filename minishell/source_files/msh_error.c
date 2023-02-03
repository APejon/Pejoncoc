/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:38:56 by amalbrei          #+#    #+#             */
/*   Updated: 2023/02/03 22:00:31 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Closes all file descriptors opened by minishell, even the ones not in
 * use
 * 
 * @param redir The 2d array that contains all redirections' data
 */
void	msh_complete_close(t_direct **redir)
{
	int	i;

	i = -1;
	while (redir[++i])
	{
		if (redir[i])
			close(redir[i]->fd);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

/**
 * @brief Prints out an error message, specifically for open() fails
 * 
 * @param shell The struct containing shell variables
 * @param redir Pointer to the redirection struct's data
 * @param err_message Error message to show
 * @param exit The exit code to be shown after error
 */
void	msh_file_error(t_shell *shell, t_direct *redir, char *err_message,
		int exit)
{
	if (redir->file)
	{
		pt_printf("minishell: %s: ", redir->file);
		pt_printf("%s\n", err_message);
	}
	shell->exit_code = exit;
}

/**
 * @brief Prints out an error message
 * 
 * @param shell The struct containing shell variables
 * @param command The struct containing the command
 * @param err_message Error message to show
 * @param exit The exit code to be shown after error
 */
void	msh_print_error(t_shell *shell, t_command *command, char *err_message,
		int exit)
{
	int	i;

	if (command->cmd_args)
	{
		i = 1;
		pt_printf("minishell: %s: ", command->cmd_args[0]);
		while (command->cmd_args[i])
		{
			pt_printf("%s: ", command->cmd_args[i]);
			i++;
		}
		pt_printf("%s\n", err_message);
	}
	shell->exit_code = exit;
}
