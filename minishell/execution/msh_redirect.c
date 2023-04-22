/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:31:59 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/21 15:40:13 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	msh_in_direct(t_shell *shell, t_direct *redir, int fd)
{
	if (redir->direct == RE_INPUT)
	{
		redir->fd = open(redir->file, O_RDONLY);
		if (redir->fd == -1)
		{
			msh_file_error(shell, redir, strerror(errno), 1);
			fd = redir->fd;
			return (fd);
		}
		fd = redir->fd;
		return (fd);
	}
	else if (redir->direct == HERE_DOC)
	{
		redir->fd = open("here_doc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (redir->fd == -1)
			msh_file_error(shell, redir, strerror(errno), 1);
		if (redir->fd != -1 && redir->hd_content != NULL)
			write(redir->fd, redir->hd_content, ft_strlen(redir->hd_content));
		fd = redir->fd;
		close(redir->fd);
		redir->fd = open("here_doc_tmp", O_RDONLY);
		return (fd);
	}
	return (fd);
}

int	msh_out_direct(t_shell *shell, t_direct *redir, int fd)
{
	if (fd != 1 && fd != -2)
		close(fd);
	if (redir->direct == RE_OUTPUT)
		redir->fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->direct == APPEND)
		redir->fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redir->fd == -1)
	{
		msh_file_error(shell, redir, strerror(errno), 1);
		fd = redir->fd;
		return (fd);
	}
	fd = redir->fd;
	return (fd);
}

int	msh_redirect(t_shell *shell, t_command *command, t_direct **redir)
{
	int	i;

	i = -1;
	while (redir[++i])
	{
		if (redir[i]->direct == RE_INPUT || redir[i]->direct == HERE_DOC)
			command->fd_in = msh_in_direct(shell, redir[i],
					command->fd_in);
		else if (redir[i]->direct == RE_OUTPUT || redir[i]->direct == APPEND)
			command->fd_out = msh_out_direct(shell, redir[i],
					command->fd_out);
		if (command->fd_in == -1 || command->fd_out == -1)
			return (1);
	}
	return (0);
}
