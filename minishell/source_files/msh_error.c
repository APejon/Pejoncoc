/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:38:56 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/17 16:45:59 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Closes fd_in and fd_outs should they contain an fd
 * 
 * @param command Struct containing the fds
 */
void	msh_conditional_close(t_command *command)
{
	if (command->fd_in != STDIN_FILENO && command->fd_in != -1)
		close(command->fd_in);
	if (command->fd_out != STDOUT_FILENO && command->fd_out != -1)
		close(command->fd_out);
	if (command->p_fd[0] != STDIN_FILENO && command->p_fd[0] != -1)
		close(command->p_fd[0]);
	if (command->p_fd[1] != STDOUT_FILENO && command->p_fd[1] != -1)
		close(command->p_fd[1]);
}

/**
 * @brief Makes sure to exit the program with the right exit number then frees
 * the malloced shell
 * 
 * @param shell The struct containing shell variables
 */
void	msh_free_to_exit(t_shell *shell)
{
	int	exit_number;

	exit_number = shell->exit_code;
	msh_complete_free(shell);
	exit(exit_number);
}

/**
 * @brief Closes all file descriptors opened by minishell, even the ones not in
 * use
 * 
 * @param redir The 2d array that contains all redirections' data
 */
void	msh_complete_close(t_shell *shell, t_command *command)
{
	int	i;

	i = -1;
	msh_conditional_close(command);
	if (command->redir)
	{
		while (command->redir[++i])
		{
			if (command->redir[i] && command->redir[i]->direct == HERE_DOC)
			{
				shell->nohd--;
				if (shell->nohd == 0)
					unlink("here_doc_tmp");
			}
			if (command->redir[i] && command->redir[i]->fd != -1
				&& command->redir[i]->fd != STDIN_FILENO)
				close(command->redir[i]->fd);
		}
	}
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
		write(2, "minishell: ", 11);
		write(2, redir->file, ft_strlen(redir->file));
		write(2, ": ", 2);
		write(2, err_message, ft_strlen(err_message));
		write(2, "\n", 1);
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
		write(2, "minishell: ", 11);
		write(2, command->cmd_args[0], ft_strlen(command->cmd_args[0]));
		write(2, ": ", 2);
		while (command->cmd_args[i])
		{
			write(2, command->cmd_args[i], ft_strlen(command->cmd_args[i]));
			write(2, ": ", 2);
			i++;
		}
		write(2, err_message, ft_strlen(err_message));
		write(2, "\n", 1);
	}
	shell->exit_code = exit;
}
