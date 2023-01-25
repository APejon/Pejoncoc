/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:31:59 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/25 21:08:30 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	msh_hd_node(t_direct *redir, t_here_doc *hd, char *content)
// {
// 	t_here_doc	*node;
// 	t_here_doc	*last;

// 	if (content != redir->file)
// 	{
// 		node = malloc(sizeof(t_here_doc));
// 		last = NULL;
// 		if (!hd)
// 		{
// 			node->content = content;
// 			node->next = NULL;
// 			hd = node;
// 		}
// 		else
// 		{
// 			last = hd;
// 			while (last->next != NULL)
// 				last = last->next;
// 			node->content = content;
// 			node->next = NULL;
// 			last->next = node;
// 		}
// 	}
// }

// int	msh_here_doc(t_direct *redir)
// {
// 	int			fd;
// 	char		*limiter;
// 	t_here_doc	*pointer;

// 	pointer = NULL;
// 	pt_printf("> ");
// 	limiter = get_next_line(0);
// 	msh_hd_node(redir, pointer, limiter);
// 	while (limiter != redir->file)
// 	{
// 		pt_printf("> ");
// 		limiter = get_next_line(0);
// 		msh_hd_node(redir, pointer, limiter);
// 	}
// 	fd = open("here_doc_tmp", O_RDWR);
// 	return (fd);
// }

int	msh_in_direct(t_shell *shell, t_command *command, t_direct *redir, int fd)
{
	int			new_fd;
	char		*limiter;
	t_here_doc	*pointer;

	new_fd = -1;
	if (fd != 0)
		close(fd);
	if (redir->direct == RE_INPUT)
	{
		new_fd = open(redir->file, O_RDONLY);
		if (new_fd == -1)
		{
			msh_print_error(shell, command, strerror(errno), 1);
			fd = new_fd;
			return (fd);
		}
		fd = new_fd;
		return (fd);
	}
	else if (redir->direct == HERE_DOC)
	{
		new_fd = msh_here_doc(redir);
		fd = new_fd;
		return (fd);
	}
}

int	msh_out_direct(t_shell *shell, t_command *command, t_direct *redir, int fd)
{
	int	new_fd;

	new_fd = -1;
	if (fd != 1)
		close(fd);
	if (redir->direct == RE_OUTPUT)
		new_fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir == APPEND)
		new_fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (new_fd == -1)
	{
		msh_print_error(shell, command, strerror(errno), 1);
		fd = new_fd;
		return (fd);
	}
	fd = new_fd;
	return (fd);
}

int	*msh_redirect(t_shell *shell, t_command *command, t_direct **redir, int *fd)
{
	int	i;

	i = -1;
	while (redir[++i] && fd[0] != -1 && fd[1] != -1)
	{
		if (redir[i] == RE_INPUT || redir[i] == HERE_DOC)
			fd[0] = msh_in_direct(shell, command, redir[i], fd[0]);
		else if (redir[i] == RE_OUTPUT || redir[i] == APPEND)
			fd[1] = msh_out_direct(shell, command, redir[i], fd[1]);
	}
	if (fd[0] == -1 || fd[1] == -1)
	{
		msh_complete_free(shell);
		exit(shell->exit_code);
	}
	else
	{
		dup2(fd[0], 0);
		dup2(fd[1], 1);
	}
}
