/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:23:05 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/29 14:57:11 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	msh_create_pipe(t_shell *shell, t_command *command, int tmp_fd)
// {
// 	if (pipe(command->p_fd) < 0)
// 	{
// 		msh_print_error(shell, command, strerror(errno), 1);
// 		exit (shell->exit_code);
// 	}
// 	command->fd_in = tmp_fd;
// 	command->fd_out = command->p_fd[1];
// }
