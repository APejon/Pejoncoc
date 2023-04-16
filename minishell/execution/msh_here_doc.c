/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:23:22 by amalbrei          #+#    #+#             */
/*   Updated: 2023/02/04 18:02:55 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Compares the size of given string and the limiter
 * 
 * @param limiter String obtained from the get_next_line function
 * @param file The limiter given from the command line
 * @return int The size of the smaller string
 */
int	msh_compare_len(char *s1, char *s2)
{
	int	len_1;
	int	len_2;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	if (len_1 <= len_2)
		return (len_1);
	else
		return (len_2);
}

/**
 * @brief Receives input from the standard input and places it within the struct
 * shell->command[]->redir[]->hd_content
 * 
 * @param redir The struct containing data related to the redirects
 */
void	msh_input_hd(t_direct *redir)
{
	int			len;
	char		*limiter;

	pt_printf("> ");
	limiter = get_next_line(0);
	len = msh_compare_len(limiter, redir->file);
	if (!ft_strncmp(limiter, redir->file, len + 1))
	{
		msh_free(&limiter);
		return ;
	}
	redir->hd_content = ft_free_strjoin(limiter, "\0", '1');
	while (1)
	{
		pt_printf("> ");
		limiter = get_next_line(0);
		len = msh_compare_len(limiter, redir->file);
		if (!ft_strncmp(limiter, redir->file, len + 1))
		{
			msh_free(&limiter);
			break ;
		}
		redir->hd_content = ft_free_strjoin(redir->hd_content, limiter, '2');
	}
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
