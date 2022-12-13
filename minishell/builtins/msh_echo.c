/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalbrei <amalbrei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:41:02 by amalbrei          #+#    #+#             */
/*   Updated: 2022/12/12 16:19:39 by amalbrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Uses the echo command to print out a message onto the shell terminal
 * 
 * @param shell The struct containing variables of used within the shell
 */
void	msh_echo(t_shell *shell)
{
	if (shell->command->flag == NULL)
		pt_printf("%s\n", shell->command->target);
	else if (!ft_strncmp(shell->command->flag, "-n", 2))
		pt_printf("%s", shell->command->target);
	else
		pt_printf("%s\n", shell->command->target);
	shell->exit_code = 0;
}
