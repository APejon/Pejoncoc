/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:23:05 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/17 17:36:17 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	msh_check_redir(t_shell *shell)
{
	int	i;
	int	found;
	int	check_failed;

	i = -1;
	found = 0;
	check_failed = 0;
	while (shell->command[++i])
	{
		if (shell->command[i]->redir)
		{
			check_failed = msh_redirect(shell, shell->command[i],
					shell->command[i]->redir);
			if (check_failed == 1)
				found = 1;
		}
	}
	if (found)
		return (1);
	return (0);
}

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
	command->fd_in = tmp_fd;
	command->fd_out = STDOUT_FILENO;
	if (command->redir)
		msh_redirect(shell, command, command->redir);
	msh_check_command_piped(shell, command, tmp_fd);
}
