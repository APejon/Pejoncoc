/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:23:05 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/10 17:02:34 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	msh_create_pipe(t_shell *shell, t_command *command, int tmp_fd)
{
	if (pipe(command->p_fd) < 0)
	{
		msh_print_error(shell, command, strerror(errno), 1);
		exit (shell->exit_code);
	}
	command->fd_in = tmp_fd;
	command->fd_out = command->p_fd[1];
}

void	msh_pipe_command(t_shell *shell, t_command *command, int *tmp_fd)
{
	msh_create_pipe(shell, command, *tmp_fd);
	if (command->redir)
		msh_redirect(shell, command, command->redir);
	msh_check_command_piped(shell, command, *tmp_fd);
	close(command->p_fd[1]);
	close(*tmp_fd);
	*tmp_fd = dup(command->p_fd[0]);
	close(command->p_fd[0]);
}

void	msh_last_command(t_shell *shell, t_command *command, int tmp_fd)
{
	command->p_fd[0] = dup(tmp_fd);
	command->fd_in = tmp_fd;
	command->fd_out = dup(STDOUT_FILENO);
	if (command->redir)
		msh_redirect(shell, command, command->redir);
	msh_check_command_piped(shell, command, tmp_fd);
	close(command->p_fd[1]);
	close(tmp_fd);
	close(command->fd_out);
}
