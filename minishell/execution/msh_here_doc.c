/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:23:22 by amalbrei          #+#    #+#             */
/*   Updated: 2023/04/21 16:15:00 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief Function representing the prompt of here_doc using get_next_line
 * 
 * @param limiter The output of a here_doc prompt
 * @param file The limiter given by the command line
 * @param len The length of how far strncmp should be read (depending on which
 * of the two variables is smaller)
 * @param nohd_c The number of here_docs presented by command line
 * @return true If here_doc prompt is successful and will be read
 * @return false If here_doc is interrupted by a signal and forced to quit
 */
bool	msh_hd_prompt(char	**limiter, char *file, int *len, int *nohd_c)
{
	*limiter = get_next_line(g_stdin);
	if (!*limiter)
	{
		(*nohd_c)--;
		if (*nohd_c == 0 && g_stdin != -3)
		{
			close(g_stdin);
			g_stdin = 0;
		}
		return (false);
	}
	*len = msh_compare_len(*limiter, file);
	return (true);
}

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

	if (s1)
		len_1 = ft_strlen(s1);
	else
		len_1 = 0;
	if (s2)
		len_2 = ft_strlen(s2);
	else
		len_2 = 0;
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
void	msh_input_hd(t_direct *redir, int *nohd_c)
{
	int			len;
	char		*limiter;

	if (g_stdin == 3)
		pt_printf("> ");
	if (!msh_hd_prompt(&limiter, redir->file, &len, nohd_c))
		return ;
	if (!ft_strncmp(limiter, redir->file, len + 1))
	{
		msh_free(&limiter);
		return ;
	}
	redir->hd_content = ft_free_strjoin(limiter, "\0", '1');
	while (1)
	{
		pt_printf("> ");
		if (!msh_hd_prompt(&limiter, redir->file, &len, nohd_c))
			break ;
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
	int	count[3];
	int	nohdc;

	count[0] = -1;
	count[2] = 0;
	nohdc = nohd;
	g_stdin = dup(STDIN_FILENO);
	while (shell->command[++count[0]] && count[2] < nohd)
	{
		count[1] = -1;
		if (shell->command[count[0]]->redir)
		{
			while (shell->command[count[0]]->redir[++count[1]])
			{
				if (shell->command[count[0]]->redir[count[1]]->direct
					== HERE_DOC)
				{
					msh_input_hd(shell->command[count[0]]->redir[count[1]],
						&nohdc);
					count[2]++;
				}
			}
		}
	}
}
