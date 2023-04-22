/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:54:37 by yhaidar           #+#    #+#             */
/*   Updated: 2023/04/22 22:06:39 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	msh_close_g_stdin(void)
{
	close(g_stdin);
	g_stdin = 0;
}

static void	msh_heredoc_prompt(void)
{
	close(g_stdin);
	printf("\n");
	g_stdin = -3;
}

static void	msh_command_prompt(void)
{
	g_stdin = 2;
}

/**
 * @brief For when sending a signal to a regular minishell prompt
 * 
 * @note The g_stdin change of value is for the exit code to be received as
 * 1 when calling the ctrl + c signal
 * 
 */
static void	msh_minishell_prompt(void)
{
	pt_printf("\n");
	g_stdin = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Signal handling the ctrl + c
 * 
 * @param signum Containing SIGINT when ctrl + c signal is called
 */
void	signal_handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		if (g_stdin == -1 || g_stdin == 1)
			msh_minishell_prompt();
		if (g_stdin == -2)
			msh_command_prompt();
		if (g_stdin == 3)
			msh_heredoc_prompt();
	}
	if (signum == SIGQUIT && (g_stdin == -1 || g_stdin == 1))
	{
	}
	if (signum == SIGQUIT && g_stdin == -2)
	{
		pt_printf("Quit:");
		pt_printf("\n");
		g_stdin = 4;
	}
}
