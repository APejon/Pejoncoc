/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:31:59 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/29 14:57:11 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	msh_in_direct(t_shell *shell, t_command *command, t_direct *redir, int fd)
{
	if (redir->direct == RE_INPUT)
	{
		redir->fd = open(redir->file, O_RDONLY);
		if (redir->fd == -1)
		{
			msh_print_error(shell, command, strerror(errno), 1);
			fd = redir->fd;
			return (fd);
		}
		fd = redir->fd;
		return (fd);
	}
	else if (redir->direct == HERE_DOC)
	{
		redir->fd = open("here_doc_tmp", O_CREAT | O_RDWR | O_TRUNC);
		write(redir->fd, redir->hd_content, ft_strlen(redir->hd_content));
		fd = redir->fd;
		return (fd);
	}
}

int	msh_out_direct(t_shell *shell, t_command *command, t_direct *redir, int fd)
{
	if (fd != 1)
		close(fd);
	if (redir->direct == RE_OUTPUT)
		redir->fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir == APPEND)
		redir->fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redir->fd == -1)
	{
		msh_print_error(shell, command, strerror(errno), 1);
		fd = redir->fd;
		return (fd);
	}
	fd = redir->fd;
	return (fd);
}

int	*msh_redirect(t_shell *shell, t_command *command, t_direct **redir)
{
	int	i;

	i = -1;
	while (redir[++i] && command->fd_in != -1 && command->fd_out != -1)
	{
		if (redir[i] == RE_INPUT || redir[i] == HERE_DOC)
			command->fd_out = msh_in_direct(shell, command, redir[i],
					command->fd_out);
		else if (redir[i] == RE_OUTPUT || redir[i] == APPEND)
			command->fd_in = msh_out_direct(shell, command, redir[i],
					command->fd_in);
	}
	if (command->fd_out == -1 || command->fd_in == -1)
	{
		msh_complete_free(shell);
		exit(shell->exit_code);
	}
}
