/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:23:22 by amalbrei          #+#    #+#             */
/*   Updated: 2023/01/29 16:35:33 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Receives input from the standard input and places it within the struct
 * shell->command[]->redir[]->hd_content
 * 
 * @param redir The struct containing data related to the redirects
 */
void	msh_input_hd(t_direct *redir)
{
	char		*limiter;

	pt_printf("> ");
	limiter = get_next_line(0);
	redir->hd_content = ft_free_strjoin(limiter, "\0", '1');
	while (limiter != redir->file)
	{
		pt_printf("> ");
		limiter = get_next_line(0);
		redir->hd_content = ft_free_strjoin(redir->hd_content, limiter, '2');
	}
	redir->hd_content = ft_free_strjoin(redir->hd_content, "\0", '1');
}

/**
 * @brief Locates the "here_doc" direct variable within each command block
 * 
 * @param shell The struct containing variables used within the shell
 * @param nohd Number of here_docs
 */
void	msh_create_here_doc(t_shell *shell, int nohd)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (shell->command[++i] && count < nohd)
	{
		j = -1;
		while (shell->command[i]->redir[++j])
		{
			if (shell->command[i]->redir[j]->direct == HERE_DOC)
			{
				msh_input_hd(shell->command[i]->redir[j]);
				count++;
			}
		}
	}
}
