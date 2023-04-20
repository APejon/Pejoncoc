/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:54:37 by yhaidar           #+#    #+#             */
/*   Updated: 2023/04/20 14:14:51 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	msh_minishell_prompt(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		if (g_stdin == -1)
			msh_minishell_prompt();
		if (g_stdin == -2)
			return ;
		if (g_stdin == 3)
		{
			close(g_stdin);
			printf("\n");
			g_stdin = -3;
		}
	}
}
